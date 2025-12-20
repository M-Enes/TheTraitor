#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <vector>
#include <memory>
#include "Battery.h"
#include "BatteryPack.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onCreateBattery();
    void onCreatePack();
    void onAddBatteryToPack();
    void onUseBattery();
    void onRechargeBattery();
    void onClearAll();

private:
    Ui::MainWindow *ui;
    
    // Data members
    std::vector<std::shared_ptr<Battery>> batteries;
    std::vector<std::shared_ptr<BatteryPack>> batteryPacks;
    
    // Helper methods
    void updateBatteryList();
    void updatePackList();
    void updateInfoPanel();
    void drawBatteries(QPainter &painter);
    void drawBattery(QPainter &painter, int x, int y, int width, int height, 
                     double chargePercent, const QString &label);
    void drawBatteryPack(QPainter &painter, std::shared_ptr<BatteryPack> pack, 
                         int x, int y);
};
#endif // MAINWINDOW_H
