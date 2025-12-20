#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <QInputDialog>
#include <QMessageBox>
#include <QColorDialog>
#include <sstream>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    setWindowTitle("Battery System Manager - Group 19");
    resize(1200, 700);
    
    // Connect signals
    connect(ui->btnCreateBattery, &QPushButton::clicked, this, &MainWindow::onCreateBattery);
    connect(ui->btnCreatePack, &QPushButton::clicked, this, &MainWindow::onCreatePack);
    connect(ui->btnAddToPack, &QPushButton::clicked, this, &MainWindow::onAddBatteryToPack);
    connect(ui->btnUse, &QPushButton::clicked, this, &MainWindow::onUseBattery);
    connect(ui->btnRecharge, &QPushButton::clicked, this, &MainWindow::onRechargeBattery);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::onClearAll);
    
    // Connect list selections to update info panel
    connect(ui->listBatteries, &QListWidget::currentRowChanged, this, &MainWindow::updateInfoPanel);
    connect(ui->listPacks, &QListWidget::currentRowChanged, this, &MainWindow::updateInfoPanel);
    
    updateInfoPanel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCreateBattery() {
    bool ok;
    double voltage = QInputDialog::getDouble(this, "Create Battery", "Enter Voltage (V):", 
                                            3.7, 0.1, 100.0, 1, &ok);
    if (!ok) return;
    
    double capacity = QInputDialog::getDouble(this, "Create Battery", "Enter Capacity (mAh):", 
                                             2000.0, 1.0, 100000.0, 1, &ok);
    if (!ok) return;
    
    QString type = QInputDialog::getText(this, "Create Battery", "Enter Battery Type:", 
                                        QLineEdit::Normal, "Li-ion", &ok);
    if (!ok || type.isEmpty()) type = "Li-ion";
    
    auto battery = std::make_shared<Battery>(voltage, capacity, type.toStdString());
    batteries.push_back(battery);
    
    updateBatteryList();
    updateInfoPanel();
    update(); // Trigger repaint
}

void MainWindow::onCreatePack() {
    QStringList items;
    items << "SERIES" << "PARALLEL";
    
    bool ok;
    QString item = QInputDialog::getItem(this, "Create Battery Pack", 
                                        "Select Connection Type:", items, 0, false, &ok);
    if (!ok) return;
    
    QString name = QInputDialog::getText(this, "Create Battery Pack", "Enter Pack Name:", 
                                        QLineEdit::Normal, "Battery Pack", &ok);
    if (!ok || name.isEmpty()) name = "Battery Pack";
    
    ConnectionType type = (item == "SERIES") ? ConnectionType::SERIES : ConnectionType::PARALLEL;
    auto pack = std::make_shared<BatteryPack>(type, name.toStdString());
    batteryPacks.push_back(pack);
    
    updatePackList();
    updateInfoPanel();
    update(); // Trigger repaint
}

void MainWindow::onAddBatteryToPack() {
    if (batteries.empty()) {
        QMessageBox::warning(this, "No Batteries", "Please create batteries first!");
        return;
    }
    
    if (batteryPacks.empty()) {
        QMessageBox::warning(this, "No Packs", "Please create a battery pack first!");
        return;
    }
    
    // Select battery
    QStringList batteryItems;
    for (size_t i = 0; i < batteries.size(); ++i) {
        batteryItems << QString::fromStdString(batteries[i]->getInfo());
    }
    
    bool ok;
    QString batteryItem = QInputDialog::getItem(this, "Select Battery", 
                                               "Choose a battery to add:", 
                                               batteryItems, 0, false, &ok);
    if (!ok) return;
    
    int batteryIndex = batteryItems.indexOf(batteryItem);
    
    // Select pack
    QStringList packItems;
    for (size_t i = 0; i < batteryPacks.size(); ++i) {
        packItems << QString::fromStdString(batteryPacks[i]->getName());
    }
    
    QString packItem = QInputDialog::getItem(this, "Select Pack", 
                                            "Choose a pack to add battery to:", 
                                            packItems, 0, false, &ok);
    if (!ok) return;
    
    int packIndex = packItems.indexOf(packItem);
    
    // Add battery to pack
    batteryPacks[packIndex]->addBattery(batteries[batteryIndex]);
    
    QMessageBox::information(this, "Success", "Battery added to pack!");
    updatePackList();
    updateInfoPanel();
    update(); // Trigger repaint
}

void MainWindow::onUseBattery() {
    int currentBattery = ui->listBatteries->currentRow();
    int currentPack = ui->listPacks->currentRow();
    
    bool ok;
    double amount = QInputDialog::getDouble(this, "Use Battery/Pack", 
                                           "Enter amount to use (mAh):", 
                                           100.0, 1.0, 100000.0, 1, &ok);
    if (!ok) return;
    
    if (currentBattery >= 0 && currentBattery < static_cast<int>(batteries.size())) {
        bool success = batteries[currentBattery]->use(amount);
        if (success) {
            QMessageBox::information(this, "Success", "Battery used successfully!");
        } else {
            QMessageBox::warning(this, "Failed", "Insufficient charge!");
        }
    } else if (currentPack >= 0 && currentPack < static_cast<int>(batteryPacks.size())) {
        bool success = batteryPacks[currentPack]->use(amount);
        if (success) {
            QMessageBox::information(this, "Success", "Battery pack used successfully!");
        } else {
            QMessageBox::warning(this, "Failed", "Insufficient charge!");
        }
    } else {
        QMessageBox::warning(this, "No Selection", "Please select a battery or pack!");
        return;
    }
    
    updateInfoPanel();
    update(); // Trigger repaint
}

void MainWindow::onRechargeBattery() {
    int currentBattery = ui->listBatteries->currentRow();
    int currentPack = ui->listPacks->currentRow();
    
    bool ok;
    double amount = QInputDialog::getDouble(this, "Recharge Battery/Pack", 
                                           "Enter amount to recharge (mAh, 0 for full):", 
                                           0.0, 0.0, 100000.0, 1, &ok);
    if (!ok) return;
    
    if (currentBattery >= 0 && currentBattery < static_cast<int>(batteries.size())) {
        if (amount > 0) {
            batteries[currentBattery]->recharge(amount);
        } else {
            batteries[currentBattery]->fullRecharge();
        }
        QMessageBox::information(this, "Success", "Battery recharged!");
    } else if (currentPack >= 0 && currentPack < static_cast<int>(batteryPacks.size())) {
        if (amount > 0) {
            batteryPacks[currentPack]->recharge(amount);
        } else {
            batteryPacks[currentPack]->fullRecharge();
        }
        QMessageBox::information(this, "Success", "Battery pack recharged!");
    } else {
        QMessageBox::warning(this, "No Selection", "Please select a battery or pack!");
        return;
    }
    
    updateInfoPanel();
    update(); // Trigger repaint
}

void MainWindow::onClearAll() {
    auto reply = QMessageBox::question(this, "Clear All", 
                                      "Are you sure you want to clear all batteries and packs?",
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        batteries.clear();
        batteryPacks.clear();
        updateBatteryList();
        updatePackList();
        updateInfoPanel();
        update(); // Trigger repaint
    }
}

void MainWindow::updateBatteryList() {
    ui->listBatteries->clear();
    for (size_t i = 0; i < batteries.size(); ++i) {
        QString text = QString("Battery %1: %2")
                          .arg(i + 1)
                          .arg(QString::fromStdString(batteries[i]->getInfo()));
        ui->listBatteries->addItem(text);
    }
}

void MainWindow::updatePackList() {
    ui->listPacks->clear();
    for (size_t i = 0; i < batteryPacks.size(); ++i) {
        QString text = QString("Pack %1: %2 (%3 batteries, %4V, %5%)")
                          .arg(i + 1)
                          .arg(QString::fromStdString(batteryPacks[i]->getName()))
                          .arg(batteryPacks[i]->getBatteryCount())
                          .arg(batteryPacks[i]->getTotalVoltage(), 0, 'f', 2)
                          .arg(batteryPacks[i]->getChargePercentage(), 0, 'f', 1);
        ui->listPacks->addItem(text);
    }
}

void MainWindow::updateInfoPanel() {
    int currentBattery = ui->listBatteries->currentRow();
    int currentPack = ui->listPacks->currentRow();
    
    QString info;
    
    if (currentBattery >= 0 && currentBattery < static_cast<int>(batteries.size())) {
        auto battery = batteries[currentBattery];
        info = QString("=== Battery %1 ===\n").arg(currentBattery + 1);
        info += QString("Type: %1\n").arg(QString::fromStdString(battery->getType()));
        info += QString("Voltage: %1 V\n").arg(battery->getVoltage(), 0, 'f', 2);
        info += QString("Capacity: %1 mAh\n").arg(battery->getCapacity(), 0, 'f', 2);
        info += QString("Current Charge: %1 mAh\n").arg(battery->getCurrentCharge(), 0, 'f', 2);
        info += QString("Charge Level: %1%\n").arg(battery->getChargePercentage(), 0, 'f', 1);
        info += battery->isFull() ? "Status: FULL\n" : "";
        info += battery->isEmpty() ? "Status: EMPTY\n" : "";
    } else if (currentPack >= 0 && currentPack < static_cast<int>(batteryPacks.size())) {
        auto pack = batteryPacks[currentPack];
        info = QString("=== Battery Pack %1 ===\n").arg(currentPack + 1);
        info += QString("Name: %1\n").arg(QString::fromStdString(pack->getName()));
        info += QString("Connection: %1\n").arg(QString::fromStdString(pack->getConnectionTypeString()));
        info += QString("Battery Count: %1\n").arg(pack->getBatteryCount());
        info += QString("Total Voltage: %1 V\n").arg(pack->getTotalVoltage(), 0, 'f', 2);
        info += QString("Total Capacity: %1 mAh\n").arg(pack->getTotalCapacity(), 0, 'f', 2);
        info += QString("Current Charge: %1 mAh\n").arg(pack->getCurrentCharge(), 0, 'f', 2);
        info += QString("Charge Level: %1%\n").arg(pack->getChargePercentage(), 0, 'f', 1);
    } else {
        info = "=== Battery System Manager ===\n\n";
        info += QString("Total Batteries: %1\n").arg(batteries.size());
        info += QString("Total Packs: %1\n\n").arg(batteryPacks.size());
        info += "Select a battery or pack to view details.";
    }
    
    ui->textInfo->setPlainText(info);
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QMainWindow::paintEvent(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    drawBatteries(painter);
}

void MainWindow::drawBatteries(QPainter &painter) {
    // Drawing area starts after the control panel
    int startX = 650;
    int startY = 50;
    int spacing = 20;
    int currentY = startY;
    
    // Draw individual batteries
    painter.setPen(QPen(Qt::black, 2));
    painter.setFont(QFont("Arial", 9));
    
    for (size_t i = 0; i < batteries.size(); ++i) {
        QString label = QString("B%1").arg(i + 1);
        drawBattery(painter, startX, currentY, 60, 100, 
                   batteries[i]->getChargePercentage(), label);
        currentY += 120;
    }
    
    // Draw battery packs
    currentY = startY;
    int packX = startX + 200;
    
    for (size_t i = 0; i < batteryPacks.size(); ++i) {
        drawBatteryPack(painter, batteryPacks[i], packX, currentY);
        currentY += 200;
    }
}

void MainWindow::drawBattery(QPainter &painter, int x, int y, int width, int height, 
                            double chargePercent, const QString &label) {
    // Battery body
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::white);
    painter.drawRect(x, y, width, height);
    
    // Battery terminal (top)
    int terminalWidth = width / 3;
    int terminalHeight = 8;
    painter.drawRect(x + (width - terminalWidth) / 2, y - terminalHeight, 
                    terminalWidth, terminalHeight);
    
    // Charge level
    int chargeHeight = static_cast<int>(height * chargePercent / 100.0);
    
    // Color based on charge level
    QColor chargeColor;
    if (chargePercent > 60) {
        chargeColor = QColor(76, 175, 80); // Green
    } else if (chargePercent > 20) {
        chargeColor = QColor(255, 193, 7); // Yellow
    } else {
        chargeColor = QColor(244, 67, 54); // Red
    }
    
    painter.setBrush(chargeColor);
    painter.drawRect(x + 2, y + height - chargeHeight, width - 4, chargeHeight - 2);
    
    // Label
    painter.setPen(Qt::black);
    painter.drawText(x, y + height + 15, width, 20, Qt::AlignCenter, label);
    
    // Percentage
    QString percentText = QString("%1%").arg(static_cast<int>(chargePercent));
    painter.drawText(x, y + height + 30, width, 20, Qt::AlignCenter, percentText);
}

void MainWindow::drawBatteryPack(QPainter &painter, std::shared_ptr<BatteryPack> pack, 
                                int x, int y) {
    if (!pack || pack->getBatteryCount() == 0) return;
    
    int batteryWidth = 50;
    int batteryHeight = 80;
    int spacing = 10;
    
    // Draw pack border
    painter.setPen(QPen(Qt::blue, 3, Qt::DashLine));
    painter.setBrush(Qt::NoBrush);
    
    if (pack->getConnectionType() == ConnectionType::SERIES) {
        // SERIES: Vertical stack
        int packHeight = pack->getBatteryCount() * (batteryHeight + spacing) + spacing;
        painter.drawRect(x - 10, y - 10, batteryWidth + 20, packHeight + 10);
        
        // Draw label
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.drawText(x - 10, y - 25, batteryWidth + 20, 20, Qt::AlignCenter, 
                        QString::fromStdString(pack->getName()));
        painter.drawText(x - 10, y - 10, batteryWidth + 20, 15, Qt::AlignCenter, "SERIES");
        
        // Draw batteries
        int currentY = y;
        for (int i = 0; i < pack->getBatteryCount(); ++i) {
            auto battery = pack->getBattery(i);
            QString label = QString("B%1").arg(i + 1);
            drawBattery(painter, x, currentY, batteryWidth, batteryHeight,
                       battery->getChargePercentage(), label);
            
            // Draw connection line
            if (i < pack->getBatteryCount() - 1) {
                painter.setPen(QPen(Qt::black, 2));
                painter.drawLine(x + batteryWidth / 2, currentY + batteryHeight,
                               x + batteryWidth / 2, currentY + batteryHeight + spacing);
            }
            
            currentY += batteryHeight + spacing;
        }
    } else {
        // PARALLEL: Horizontal arrangement
        int packWidth = pack->getBatteryCount() * (batteryWidth + spacing) + spacing;
        painter.drawRect(x - 10, y - 10, packWidth + 10, batteryHeight + 20);
        
        // Draw label
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.drawText(x - 10, y - 25, packWidth + 10, 20, Qt::AlignCenter, 
                        QString::fromStdString(pack->getName()));
        painter.drawText(x - 10, y - 10, packWidth + 10, 15, Qt::AlignCenter, "PARALLEL");
        
        // Draw batteries
        int currentX = x;
        for (int i = 0; i < pack->getBatteryCount(); ++i) {
            auto battery = pack->getBattery(i);
            QString label = QString("B%1").arg(i + 1);
            drawBattery(painter, currentX, y, batteryWidth, batteryHeight,
                       battery->getChargePercentage(), label);
            
            // Draw connection line
            if (i < pack->getBatteryCount() - 1) {
                painter.setPen(QPen(Qt::black, 2));
                painter.drawLine(currentX + batteryWidth, y + batteryHeight / 2,
                               currentX + batteryWidth + spacing, y + batteryHeight / 2);
            }
            
            currentX += batteryWidth + spacing;
        }
    }
    
    // Draw pack info
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 8));
    QString packInfo = QString("%1V, %2%")
                          .arg(pack->getTotalVoltage(), 0, 'f', 1)
                          .arg(pack->getChargePercentage(), 0, 'f', 0);
    
    if (pack->getConnectionType() == ConnectionType::SERIES) {
        int packHeight = pack->getBatteryCount() * (batteryHeight + spacing);
        painter.drawText(x - 10, y + packHeight + 20, batteryWidth + 20, 20, 
                        Qt::AlignCenter, packInfo);
    } else {
        int packWidth = pack->getBatteryCount() * (batteryWidth + spacing);
        painter.drawText(x, y + batteryHeight + 20, packWidth, 20, 
                        Qt::AlignCenter, packInfo);
    }
}

