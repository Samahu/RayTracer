#include "RenderArea.h"

#include <SceneObjects/CompositeSceneObject.hpp>
#include <SceneObjects/Sphere.hpp>

#include <QMessageBox>

using namespace std;

RenderArea::RenderArea(QWidget *parent)
    : QLabel(parent),
      buffer(200, 100, QImage::Format_RGB32)
{
    rendererType = RendererType::SimpleRTf;
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}

void RenderArea::resizeEvent(QResizeEvent *e)
{
    displayBuffer(this->width(), this->height());
}

void RenderArea::setRendererType(RendererType rendererType)
{
    this->rendererType = rendererType;

    vector<Vector3<int>> results;

    switch (rendererType)
    {
    case RendererType::SimpleRTf:
        results = renderSimpleRTf();
        break;
    case RendererType::SimpleRTd:
        results = renderSimpleRTd();
        break;
    }

    updateBuffer(results);
    displayBuffer(this->width(), this->height());
}

vector<Vector3<int>> RenderArea::renderSimpleRTf()
{
    auto w = buffer.width();
    auto h = buffer.height();

    // Construct world
    auto world = std::make_unique<CompositeSceneObject<float>>();
    auto sphere1 = std::make_unique<Sphere<float>>(Vector3<float>{ 0.0, 0.0, -1.0 }, 0.5);
    world->Add(std::move(sphere1));
    auto sphere2 = std::make_unique<Sphere<float>>(Vector3<float>{ 1.5, 0.0, -1.0 }, 0.5);
    world->Add(std::move(sphere2));
    auto simpleRTd = SimpleRT<float>();

    return simpleRTd.Render(w, h, *world);
}

vector<Vector3<int>> RenderArea::renderSimpleRTd()
{
    auto w = buffer.width();
    auto h = buffer.height();

    // Construct world
    auto world = std::make_unique<CompositeSceneObject<double>>();
    auto sphere1 = std::make_unique<Sphere<double>>(Vector3<double>{ 0.0, 0.0, -1.0 }, 0.5);
    world->Add(std::move(sphere1));
    auto sphere2 = std::make_unique<Sphere<double>>(Vector3<double>{ 1.5, 0.0, -1.0 }, 0.5);
    world->Add(std::move(sphere2));
    auto simpleRTd = SimpleRT<double>();

    return simpleRTd.Render(w, h, *world);
}

void RenderArea::updateBuffer(const std::vector<Vector3<int>>& results)
{
    auto w = buffer.width();
    auto h = buffer.height();

    for (auto y = 0; y < h; ++y)
    {
        auto line = reinterpret_cast<QRgb*>(buffer.scanLine(y));
        for (auto x = 0; x < w; ++x)
        {
            auto idx = static_cast<size_t>(y * w + x);
            auto c = results[idx];
            auto q = QColor{c.x(), c.y(), c.z()};
            line[x] = q.rgb();
        }
    }
}

void RenderArea::displayBuffer(int w, int h)
{
    pixmap = QPixmap::fromImage(buffer);
    pixmap = pixmap.scaled(QSize(w, h), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    this->setPixmap(pixmap);
}
