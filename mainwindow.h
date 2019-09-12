#include <QMainWindow>
#include <QTimer>
#include <QPaintEvent>
#include <QPainter>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow() : QMainWindow(nullptr)
    {
        setWindowTitle("中秋快乐~");
        setMinimumSize(234, 234);

        // 每20毫秒重新绘制一次界面
        QTimer* timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        timer->start(20);
    }

protected:
    void paintEvent(QPaintEvent*) override
    {
        // 挡住区域相对于月亮的偏移循环
        static int pos = -threshold;
        if (++pos > threshold) // 右边界时回到左边界
            pos = -threshold;

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿

        // 画黑色夜空背景
        painter.fillRect(QRect(0,0,width(),height()), QBrush(QColor(5,17,33)));

        // 完整月亮
        QPainterPath moon_path;
        moon_path.addEllipse(width()/2-radius/2,   height()/2-radius/2, radius, radius);

        // 月亮被挡住的一部分
        QPainterPath cut_path;
        cut_path.addEllipse(width()/2-radius/2+pos,height()/2-radius/2, radius, radius);

        // 完整月亮 - 挡住区域 = 画出来的区域
        moon_path -= cut_path;
        painter.fillPath(moon_path, QColor(247,235,195));
    }

private:
    const int radius    = 100; // 月亮半径
    const int threshold = 110; // 一个周期后停顿一下，显示圆滚滚的月亮
};
