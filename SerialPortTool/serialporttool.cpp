﻿#include "serialporttool.h"
#include "ui_serialporttool.h"

#pragma execution_character_set("utf-8")

MyPushButton::MyPushButton(QWidget *parent) :
    QPushButton(parent)
{

}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if (Qt::LeftButton == e->button())
    {
        emit leftButtonClicked();
    }
    else if (Qt::RightButton == e->button())
    {
        emit rightButtonClicked();
    }
}

MyPushButton::~MyPushButton()
{
    //delete ui;
}

bool SerialPortTool::open_serial()
{
    this->serialPort = new QSerialPort;
    this->serialPort->setPortName(ui->comboBox_com_list->currentText());
    if(!this->serialPort->open(QIODevice::ReadWrite))
    {
        return false;
    }

#if 1
    this->serialPort->setBaudRate(ui->comboBox_baudrate_list->currentText().toInt());

    switch(ui->comboBox_data_bit_list->currentIndex())
    {
        case 0:
            this->serialPort->setDataBits(QSerialPort::Data5);
            break;

        case 1:
            this->serialPort->setDataBits(QSerialPort::Data6);
            break;

        case 2:
            this->serialPort->setDataBits(QSerialPort::Data7);
            break;

        case 3:
        default:
            this->serialPort->setDataBits(QSerialPort::Data8);
    }

    switch(ui->comboBox_check_bit_list->currentIndex())
    {
        case 0:
            this->serialPort->setParity(QSerialPort::NoParity);
            break;

        case 1:
            this->serialPort->setParity(QSerialPort::OddParity);
            break;

        case 2:
            this->serialPort->setParity(QSerialPort::EvenParity);
            break;

        case 3:
            this->serialPort->setParity(QSerialPort::SpaceParity);
            break;

        case 4:
            this->serialPort->setParity(QSerialPort::MarkParity);
            break;

        default:
            this->serialPort->setParity(QSerialPort::NoParity);
    }

    switch(ui->comboBox_stop_bit_list->currentIndex())
    {
        case 0:
            this->serialPort->setStopBits(QSerialPort::OneStop);
            break;

        case 1:
            this->serialPort->setStopBits(QSerialPort::OneAndHalfStop);
            break;

        case 2:
            this->serialPort->setStopBits(QSerialPort::TwoStop);
            break;

        default:
            this->serialPort->setStopBits(QSerialPort::OneStop);
    }

    switch(ui->comboBox_flow_control_list->currentIndex())
    {
        case 0:
            this->serialPort->setFlowControl(QSerialPort::NoFlowControl);
            break;

        case 1:
            this->serialPort->setFlowControl(QSerialPort::HardwareControl);
            break;

        case 2:
            this->serialPort->setFlowControl(QSerialPort::SoftwareControl);
            break;

        default:
            this->serialPort->setFlowControl(QSerialPort::NoFlowControl);
    }
#else

    this->serialPort->setBaudRate(115200);
    this->serialPort->setDataBits(QSerialPort::Data8);
    this->serialPort->setParity(QSerialPort::NoParity);
    this->serialPort->setStopBits(QSerialPort::OneStop);
    this->serialPort->setFlowControl(QSerialPort::NoFlowControl);
#endif
    connect(this->serialPort, &QSerialPort::readyRead, this, &SerialPortTool::ReadData);

    return true;
}

void SerialPortTool::close_serial()
{
    this->serialPort->clear();
    this->serialPort->close();
    this->serialPort->deleteLater();
    delete this->serialPort;
}

void SerialPortTool::refresh_serial()
{
    ui->comboBox_com_list->clear();

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
#if 1
        qDebug() << "Name        :" << info.portName();
        //qDebug() << "Description :" << info.description();
        //qDebug() << "Manufacturer:" << info.manufacturer();
#endif
        ui->comboBox_com_list->addItem(info.portName());
    }
}

char char_to_hex(char c)
{
    if((c >= '0') && (c <= '9'))
    {
        return c-'0';
    }
    else if((c >= 'A') && (c <= 'F'))
    {
        return c-'A';
    }
    else if((c >= 'a') && (c <= 'f'))
    {
        return c-'a';
    }
    else
    {
        return 0;
    }
}
void SerialPortTool::send_serial(QString str)
{
    char pstr[32];

    if(this->serial_open_flag)
    {
        if(!this->hex_send_flag)
        {
            if(this->display_time_flag)
            {
                QTime time = QTime::currentTime();
                this->serialPort->write(("["+time.toString("hh:mm:ss")+"]>>>").toLocal8Bit());
            }

            this->serialPort->write(str.toLocal8Bit());

            if(this->crlf_flag)
            {
                this->serialPort->write("\r\n");
                this->send_byte_count += str.length()+2;
            }
            else
            {
                this->send_byte_count += str.length();
            }

            sprintf(pstr, "Tx:%d", this->send_byte_count);
            this->label_tx_status->setText(pstr);
        }
        else
        {
            char hex_data[256];
            uint16_t index = 0;
            char *p = str.toUtf8().data();
            char hb = 0, lb = 0;

            for(int i=0; i<str.length();)
            {
                if(p[i] != ' ')
                {
                    hb = char_to_hex(p[i]);
                    lb = char_to_hex(p[i]);
                    hex_data[index++] = (hb << 4) | lb;
                    i += 2;
                }
                else
                {
                    i++;
                }
            }

            this->serialPort->write(hex_data);

            this->send_byte_count += str.length();
            sprintf(pstr, "Tx:%d", this->send_byte_count);
            this->label_tx_status->setText(pstr);
        }
    }
    else
    {
        QMessageBox::warning(this, "警告", "请打开对应的串口！！！");
    }
}

void SerialPortTool::onTimerOut()
{
#if 0
    QTime time = QTime::currentTime();
    ui->lcdNumber_time->display(time.toString("hh:mm:ss"));
#else
    QDateTime dateTime = QDateTime::currentDateTime();
    ui->lcdNumber_time->display(dateTime.toString("yyyy-MM-dd hh:mm:ss"));
#endif

    // generate some data:
    QVector<double> x(1), y(1); // initialize with entries 0..100

    static uint32_t x_index = 0;
    static uint32_t y_index = 0;
    static uint32_t beix = 1;
    static uint32_t beiy = 2;

    x[0] = x_index * beix;
    y[0] = x_index * x_index * beiy;
    x_index++;
    y_index++;

    ui->customplot_data_curve->graph(0)->addData(x, y);
    ui->customplot_data_curve->rescaleAxes();
    ui->customplot_data_curve->replot();

#if 0
    ui->textEdit_Recv->moveCursor(QTextCursor::End);
    ui->textEdit_Recv->insertPlainText(time.toString("hh:mm:ss.zzz")+"\r\n");
    ui->textEdit_Recv->moveCursor(QTextCursor::End);
#endif
}

void SerialPortTool::ReadData()
{
    static QByteArray buf;
    QString str;

    buf += this->serialPort->readAll();

    if(!this->hex_recv_flag)
    {
        //为了保证中文的完整接收，此次不能简单判断是否为空。
        if(buf.endsWith("\r\n"))//!buf.isEmpty())
        {
            this->recv_textEdit_mutex.lock();
            ui->textEdit_recv->moveCursor(QTextCursor::End);

            if(this->display_time_flag)
            {
                QDateTime dateTime = QDateTime::currentDateTime();
                ui->textEdit_recv->insertPlainText("["+dateTime.toString("yyyy-MM-dd hh:mm:ss.zzz")+"]<<<");
            }

            str = QString::fromLocal8Bit(buf);
            ui->textEdit_recv->insertPlainText(str);

            ui->textEdit_recv->moveCursor(QTextCursor::End);
            this->recv_textEdit_mutex.unlock();

            if(this->auto_save_recv_flag)
            {
                this->auto_save_recv_file->write(str.toUtf8());
                this->auto_save_recv_file->flush();
            }

            this->recv_byte_count += str.length();
            char pstr[32];
            sprintf(pstr, "Rx:%d", this->recv_byte_count);
            this->label_rx_status->setText(pstr);

            buf.clear();
            str.clear();
        }
        else
        {

        }
    }
    else
    {
        if(!buf.isEmpty())
        {
            QString hex_data = buf.toHex().data();
            hex_data = hex_data.toUpper();

            QString hex_str;
            for(int i=0; i<hex_data.length(); i+=2)
            {
                QString st = hex_data.mid(i, 2);
                hex_str += st;
                hex_str += ' ';
            }

            ui->textEdit_recv->moveCursor(QTextCursor::End);
            ui->textEdit_recv->insertPlainText(hex_str);
            ui->textEdit_recv->moveCursor(QTextCursor::End);
        }

        buf.clear();
        str.clear();
    }
}

void SerialPortTool::setupQuadraticDemo(QCustomPlot *customPlot)
{
    demoName = "Quadratic Demo";
#if 0
    // generate some data:
    QVector<double> x(2000), y(2000); // initialize with entries 0..100
    for (int i=0; i<2000; ++i)
    {
        x[i] = i/50.0; // x goes from -1 to 1
        y[i] = x[i]*x[i];  // let's plot a quadratic function
    }
#endif
    // create graph and assign data to it:
    customPlot->addGraph();
    //customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(0, 200);
    customPlot->yAxis->setRange(0, 200);

    customPlot->rescaleAxes();

    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void SerialPortTool::set_config_file_default()
{
    QWidget *widget;
    int r = 0, c = 0;
    char str[32];

    this->config_file->clear();

    this->config_file->beginGroup("Config.ini");
    this->config_file->setValue("Note","非专业人员请勿乱动此文件！！！");
    this->config_file->endGroup();

    for(r=0; r<CMD_LIST_ROW; r++)
    {
        c = 0;

        sprintf(str, "cmd_str_%03d", r);
        this->config_file->beginGroup(str);

        this->config_file->setValue("hex", false);
        widget = ui->tableWidget_cmd_list->cellWidget(r+1, c++);
        QCheckBox *checkBox = (QCheckBox*)widget;
        checkBox->setCheckState(Qt::Unchecked);

        if(r<3)
        {
            sprintf(str, "test cmd demo %d", r);
            this->config_file->setValue("cmd_str", str);
            widget = ui->tableWidget_cmd_list->cellWidget(r+1, c++);
            QLineEdit *lineEdit1 = (QLineEdit*)widget;
            lineEdit1->setText(str);
        }
        else
        {
            this->config_file->setValue("cmd_str", "");
            widget = ui->tableWidget_cmd_list->cellWidget(r+1, c++);
            QLineEdit *lineEdit1 = (QLineEdit*)widget;
            lineEdit1->setText("");
        }

        sprintf(str, "cmd_%03d", r);
        this->config_file->setValue("btn_name", str);
        widget = ui->tableWidget_cmd_list->cellWidget(r+1, c++);
        MyPushButton *pushButton = (MyPushButton*)widget;
        pushButton->setText(str);

        if(r<3)
        {
            this->config_file->setValue("ser", r);
            widget = ui->tableWidget_cmd_list->cellWidget(r+1, c++);
            QLineEdit *lineEdit2 = (QLineEdit*)widget;
            lineEdit2->setText(QString::number(r));
        }
        else
        {
            this->config_file->setValue("ser", 0);
            widget = ui->tableWidget_cmd_list->cellWidget(r+1, c++);
            QLineEdit *lineEdit2 = (QLineEdit*)widget;
            lineEdit2->setText(QString::number(0));
        }

        this->config_file->setValue("delay", 1000);
        widget = ui->tableWidget_cmd_list->cellWidget(r+1, c++);
        QLineEdit *lineEdit3 = (QLineEdit*)widget;
        lineEdit3->setText(QString::number(1000));

        this->config_file->endGroup();
    }
}

void SerialPortTool::set_config_cmd_list()
{
    QWidget *widget;
    int r = 0, c = 0;
    char str[32];

    for(r=1; r<(CMD_LIST_ROW+1); r++)
    {
        c = 0;
        widget = ui->tableWidget_cmd_list->cellWidget(r, c++);
        QCheckBox *checkBox = (QCheckBox*)widget;

        widget = ui->tableWidget_cmd_list->cellWidget(r, c++);
        QLineEdit *lineEdit1 = (QLineEdit*)widget;

        widget = ui->tableWidget_cmd_list->cellWidget(r, c++);
        MyPushButton *pushButton = (MyPushButton*)widget;

        widget = ui->tableWidget_cmd_list->cellWidget(r, c++);
        QLineEdit *lineEdit2 = (QLineEdit*)widget;

        widget = ui->tableWidget_cmd_list->cellWidget(r, c++);
        QLineEdit *lineEdit3 = (QLineEdit*)widget;

        sprintf(str, "cmd_str_%03d", r-1);
        this->config_file->beginGroup(str);
        this->config_file->setValue("hex", checkBox->isChecked());
        this->config_file->setValue("cmd_str", lineEdit1->text());
        this->config_file->setValue("btn_name", pushButton->text());
        this->config_file->setValue("ser", lineEdit2->text().toInt());
        this->config_file->setValue("delay", lineEdit3->text().toInt());
        this->config_file->endGroup();
    }
}

void SerialPortTool::onCurrentLineHighLight()
{
    QTextEdit *edit = ui->textEdit_recv;
    QList<QTextEdit::ExtraSelection> extraSelection;
    QTextEdit::ExtraSelection selection;
    QColor lineColor = QColor(Qt::gray).lighter(150);

    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection,true);
    selection.cursor = edit->textCursor();
    selection.cursor.clearSelection();
    //将刚设置的 selection追加到链表当中
    extraSelection.append(selection);
    edit->setExtraSelections(extraSelection);
}

void SerialPortTool::ReadCmdList()
{
    QWidget *widget;
    int r = 0, c = 0;
    char str[32];

    for(r=1; r<(CMD_LIST_ROW+1); r++)
    {
        c = 0;

        sprintf(str, "cmd_str_%03d", r-1);
        this->config_file->beginGroup(str);

        widget = ui->tableWidget_cmd_list->cellWidget(r, c++);
        QCheckBox *checkBox = (QCheckBox*)widget;
        checkBox->setChecked(this->config_file->value("hex").toBool());

        widget = ui->tableWidget_cmd_list->cellWidget(r, c++);
        QLineEdit *lineEdit1 = (QLineEdit*)widget;
        lineEdit1->setText(this->config_file->value("cmd_str").toString());

        widget = ui->tableWidget_cmd_list->cellWidget(r, c++);
        MyPushButton *pushButton = (MyPushButton*)widget;
        pushButton->setText(this->config_file->value("btn_name").toString());

        widget = ui->tableWidget_cmd_list->cellWidget(r, c++);
        QLineEdit *lineEdit2 = (QLineEdit*)widget;
        lineEdit2->setText(this->config_file->value("ser").toString());

        widget = ui->tableWidget_cmd_list->cellWidget(r, c++);
        QLineEdit *lineEdit3 = (QLineEdit*)widget;
        lineEdit3->setText(this->config_file->value("delay").toString());

        this->config_file->endGroup();
    }
}

SerialPortTool::SerialPortTool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SerialPortTool),
    ymodemFileTransmit(new YmodemFileTransmit),
    ymodemFileReceive(new YmodemFileReceive)
{
    ui->setupUi(this);
    this->resize(QSize( 1150, 750 ));
    this->setCmdList();

    QList<int> list;
    list << 100 << 0;
    ui->splitter_curve->setSizes(list);
    ui->splitter_cmd_list->setSizes(list);
    this->display_cmd_list_flag = false;
    this->display_data_curve_flag = false;
    //no set
    this->display_serial_config_flag = true;

    this->timer = new QTimer();
    this->timer->setInterval(1000);
    this->timer->start();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));

    this->refresh_serial();

    this->setupQuadraticDemo(ui->customplot_data_curve);

    ui->comboBox_baudrate_list->setCurrentText("115200");
    ui->comboBox_data_bit_list->setCurrentText("8 bit");
    ui->comboBox_stop_bit_list->setCurrentText("1 bit");

    this->config_file_name = QCoreApplication::applicationDirPath();
    this->config_file_name += "./config.ini";
    this->config_file = new QSettings(this->config_file_name, QSettings::IniFormat);
    this->config_file->setIniCodec("UTF8");

    uint8_t init_config_flag = 0;
    this->config_file->beginGroup("Config.ini");
    QStringList config = this->config_file->childKeys();
    if(!config.empty())
    {
        init_config_flag = 1;
    }
    this->config_file->endGroup();

    if(init_config_flag)
    {
        this->ReadCmdList();
    }
    else
    {
        this->set_config_file_default();
    }

    //高亮接收窗口鼠标所在行
    connect(ui->textEdit_recv, SIGNAL(cursorPositionChanged()), this, SLOT(onCurrentLineHighLight()));
    this->highlight = new Highlighter(ui->textEdit_recv->document());

    this->config_file->beginGroup("highlight_keyword");
    QStringList kw_list =  this->config_file->childKeys();
    char *p_str = nullptr;
    foreach(QString key, kw_list)
    {
        p_str = this->config_file->value(key).toString().toLocal8Bit().data();
        this->keyword_list << p_str;
    }
    this->config_file->endGroup();
    this->highlight->setTextQueue(this->keyword_list);

    ui->statusBar->showMessage(tr("程序启动成功!"), 2000);
    this->label_tx_status = new QLabel();
    this->label_tx_status->setMinimumSize(84, 20);
    this->label_tx_status->setText("Tx:0");
    ui->statusBar->addPermanentWidget(this->label_tx_status);
    this->label_rx_status = new QLabel();
    this->label_rx_status->setMinimumSize(84, 20);
    this->label_rx_status->setText("Rx:0");
    ui->statusBar->addPermanentWidget(this->label_rx_status);

    this->qProgressBar = new QProgressBar();
    this->qProgressBar->setMinimumSize(256, 20);
    this->qProgressBar->setMaximumSize(256, 20);
    ui->statusBar->addPermanentWidget(this->qProgressBar);

    ui->comboBox_send_protocol->addItem("ymodem");

    this->transmitButtonStatus = false;
    this->receiveButtonStatus  = false;
    connect(ymodemFileTransmit, SIGNAL(transmitProgress(int)), this, SLOT(transmitProgress(int)));
    connect(ymodemFileReceive, SIGNAL(receiveProgress(int)), this, SLOT(receiveProgress(int)));
    connect(ymodemFileTransmit, SIGNAL(transmitStatus(YmodemFileTransmit::Status)), this, SLOT(transmitStatus(YmodemFileTransmit::Status)));
    connect(ymodemFileReceive, SIGNAL(receiveStatus(YmodemFileReceive::Status)), this, SLOT(receiveStatus(YmodemFileReceive::Status)));

    //eg:crc
    const char myString[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};
    uint32_t crc = CRC::Calculate(myString, sizeof(myString), CRC::CRC_16_MODBUS());
    char str[32];
    sprintf(str, "CRC:0x%04X\r\n", crc);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(str);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
}

SerialPortTool::~SerialPortTool()
{
    QWidget *widget;
    int r = 0, c = 0;

    delete ui;

    for(r=1; r<(CMD_LIST_ROW+1); r++)
    {
        c = 0;
        widget = ui->tableWidget_cmd_list->cellWidget(r, c++);
        QCheckBox *checkBox = (QCheckBox*)widget;
        delete checkBox;

        widget = ui->tableWidget_cmd_list->cellWidget(r, c++);
        QLineEdit *lineEdit1 = (QLineEdit*)widget;
        delete lineEdit1;

        widget = ui->tableWidget_cmd_list->cellWidget(r, c++);
        MyPushButton *pushButton = (MyPushButton*)widget;
        delete pushButton;

        widget = ui->tableWidget_cmd_list->cellWidget(r, c++);
        QLineEdit *lineEdit2 = (QLineEdit*)widget;
        delete lineEdit2;

        widget = ui->tableWidget_cmd_list->cellWidget(r, c++);
        QLineEdit *lineEdit3 = (QLineEdit*)widget;
        delete lineEdit3;
    }

    delete timer;
    delete config_file;
    delete highlight;
    delete qProgressBar;
    delete label_tx_status;
    delete label_rx_status;

    if(auto_save_recv_file != nullptr)
    {
        delete auto_save_recv_file;
    }

    if(serialPort != nullptr)
    {
        delete serialPort;
    }

    //delete ymodemFileTransmit;
    //delete ymodemFileReceive;
}

void SerialPortTool::setCmdList()
{
    ui->tableWidget_cmd_list->verticalHeader()->setVisible(false);
    ui->tableWidget_cmd_list->horizontalHeader()->setVisible(false);
    ui->tableWidget_cmd_list->setShowGrid(false);

    char str[32];
    for(int r=0; r<(CMD_LIST_ROW+1); r++)
    {
        for(int c=0; c<CMD_LIST_COL; c++)
        {
            if(r == 0)
            {
                QLabel *label = new QLabel();

                switch(c)
                {
                    case 0:
                        label->setText("Hex");
                        break;

                    case 1:
                        label->setText("    命令字串");
                        break;

                    case 2:
                        label->setText("    发送");
                        break;

                    case 3:
                        label->setText("序号");
                        break;

                    case 4:
                        label->setText("    延时");
                        break;

                    default:
                        ;
                }
                ui->tableWidget_cmd_list->setCellWidget(r, c, label);
                continue;
            }

            switch(c)
            {
                case 0:
                    {
                        QCheckBox *checkBox = new QCheckBox();

                        ui->tableWidget_cmd_list->setCellWidget(r, c, checkBox);
                    }
                    break;

                case 1:
                    {
                        QLineEdit *lineEdit = new QLineEdit();

                        if(r < 4)
                        {
                            sprintf(str, "test cmd demo %d", r-1);
                            lineEdit->setText(str);
                        }
                        else
                        {
                            lineEdit->setText("");
                        }

                        ui->tableWidget_cmd_list->setCellWidget(r, c, lineEdit);
                    }
                    break;

                case 2:
                    {
                        MyPushButton *pushButton = new MyPushButton();
                        sprintf(str, "cmd_%03d", r);
                        pushButton->setText(str);

                        ui->tableWidget_cmd_list->setCellWidget(r, c, pushButton);

                        connect(pushButton, SIGNAL(leftButtonClicked()), this, SLOT(OnBtnLeftClicked()));
                        connect(pushButton, SIGNAL(rightButtonClicked()), this, SLOT(OnBtnRightClicked()));
                    }
                    break;

                case 3:
                    {
                        QLineEdit *lineEdit = new QLineEdit();

                        if(r < 4)
                        {
                            sprintf(str, "%d", r-1);
                            lineEdit->setText(str);
                        }
                        else
                        {
                            lineEdit->setText("");
                        }

                        ui->tableWidget_cmd_list->setCellWidget(r, c, lineEdit);
                    }
                    break;

                case 4:
                    {
                        QLineEdit *lineEdit = new QLineEdit();

                        sprintf(str, "1000");
                        lineEdit->setText(str);

                        ui->tableWidget_cmd_list->setCellWidget(r, c, lineEdit);
                    }
                    break;

                default:
                    ;
            }
        }
    }

    //ui->tableWidget_cmd_list->resizeRowsToContents();
    ui->tableWidget_cmd_list->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    ui->tableWidget_cmd_list->setColumnWidth(1, 200);
    ui->tableWidget_cmd_list->setColumnWidth(2, 94);
    ui->tableWidget_cmd_list->setColumnWidth(3, 28);
    ui->tableWidget_cmd_list->setColumnWidth(4, 54);
    ui->tableWidget_cmd_list->setAlternatingRowColors(true);
    ui->tableWidget_cmd_list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void SerialPortTool::OnBtnLeftClicked()
{
    MyPushButton *senderObj = qobject_cast<MyPushButton*>(sender());
    if(senderObj == nullptr)
    {
        return;
    }

    QModelIndex idx = ui->tableWidget_cmd_list->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    int row = idx.row();
    int column = idx.column();
#if 0
    char str[32];

    sprintf(str, "OnBtnLeftClicked[%d, %d]\r\n", row, column);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(str);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
#endif
    QWidget *widget = ui->tableWidget_cmd_list->cellWidget(row, column-1);
    QLineEdit *lineEdit = (QLineEdit*)widget;

    QString str_cmd = lineEdit->text();

    this->send_serial(str_cmd);
}

void SerialPortTool::OnBtnRightClicked()
{
    MyPushButton *senderObj = qobject_cast<MyPushButton*>(sender());
    if(senderObj == nullptr)
    {
        return;
    }

    QModelIndex idx = ui->tableWidget_cmd_list->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    int row = idx.row();
    int column = idx.column();
#if 1
    char str[32];

    sprintf(str, "OnBtnRightClicked[%d, %d]\r\n", row, column);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(str);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
#endif
    QWidget *widget = ui->tableWidget_cmd_list->cellWidget(row, column);
    MyPushButton *pushButton = (MyPushButton*)widget;

    bool ok = false;
    QString text = QInputDialog::getText(this, "请输入备注信息：", "备注名：",
                                         QLineEdit::Normal, QString::null,
                                         &ok);
    if(ok && !text.isEmpty())
    {
        pushButton->setText(text);
    }
    else
    {
        //cancel;
    }
}

void SerialPortTool::on_comboBox_baudrate_list_activated(const QString &arg1)
{
    char buf[64];

    sprintf(buf, "on_comboBox_baudrate_list_activated %s\r\n", arg1.toUtf8().data());
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);

    if(this->serial_open_flag)
    {
        this->serial_open_flag = false;
        ui->pushButton_open_serial->setText("打开串口");
        this->close_serial();
    }
}

void SerialPortTool::on_comboBox_data_bit_list_activated(const QString &arg1)
{
    char buf[64];

    sprintf(buf, "on_comboBox_data_bit_list_activated %s\r\n", arg1.toUtf8().data());
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);

    if(this->serial_open_flag)
    {
        this->serial_open_flag = false;
        ui->pushButton_open_serial->setText("打开串口");
        this->close_serial();
    }
}

void SerialPortTool::on_comboBox_stop_bit_list_activated(const QString &arg1)
{
    char buf[64];

    sprintf(buf, "on_comboBox_stop_bit_list_activated %s\r\n", arg1.toUtf8().data());
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);

    if(this->serial_open_flag)
    {
        this->serial_open_flag = false;
        ui->pushButton_open_serial->setText("打开串口");
        this->close_serial();
    }
}

void SerialPortTool::on_comboBox_check_bit_list_activated(const QString &arg1)
{
    char buf[64];

    sprintf(buf, "on_comboBox_check_bit_list_activated %s\r\n", arg1.toUtf8().data());
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);

    if(this->serial_open_flag)
    {
        this->serial_open_flag = false;
        ui->pushButton_open_serial->setText("打开串口");
        this->close_serial();
    }
}

void SerialPortTool::on_comboBox_flow_control_list_activated(const QString &arg1)
{
    char buf[64];

    sprintf(buf, "on_comboBox_flow_control_list_activated %s\r\n", arg1.toUtf8().data());
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);

    if(this->serial_open_flag)
    {
        this->serial_open_flag = false;
        ui->pushButton_open_serial->setText("打开串口");
        this->close_serial();
    }
}

void SerialPortTool::on_pushButton_open_serial_clicked()
{
    if(!this->serial_open_flag)
    {
        if(this->open_serial())
        {
            this->serial_open_flag = true;
            ui->pushButton_open_serial->setText("关闭串口");
        }
        else
        {
            QMessageBox::warning(this, "警告", "***串口已被其他程序打开***");
        }
    }
    else
    {
        this->serial_open_flag = false;
        ui->pushButton_open_serial->setText("打开串口");
        this->close_serial();
    }
}

void SerialPortTool::on_pushButton_refresh_serial_clicked()
{
    if(this->serial_open_flag)
    {
        this->serial_open_flag = false;
        ui->pushButton_open_serial->setText("打开串口");
        this->close_serial();
    }

    this->refresh_serial();
}

void SerialPortTool::on_checkBox_rts_stateChanged(int arg1)
{
    char buf[64];

    sprintf(buf, "on_checkBox_rts_stateChanged %d\r\n", arg1);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
}

void SerialPortTool::on_checkBox_dtr_stateChanged(int arg1)
{
    char buf[64];

    sprintf(buf, "on_checkBox_dtr_stateChanged %d\r\n", arg1);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
}

void SerialPortTool::on_checkBox_autosave_stateChanged(int arg1)
{
    char default_str[64];
    bool ok = false;

    QDateTime dateTime = QDateTime::currentDateTime();
    sprintf(default_str, "AutoSave-%s-%s.txt", ui->comboBox_com_list->currentText().toLocal8Bit().data(),
            dateTime.toString("yyyy-MM-dd_hh-mm-ss").toLocal8Bit().data());

    if(arg1 == 2)
    {
        QString text = QInputDialog::getText(this, tr("自动保存接收信息"),
                            tr("文件名:"), QLineEdit::Normal, default_str, &ok);
        this->auto_save_recv_file = new QFile("./"+text);
        if(ok && !text.isEmpty())
        {
            this->auto_save_recv_file->open(QIODevice::WriteOnly/* | QIODevice::Text*/);
            //this->auto_save_recv_file->write(txt.toUtf8());
        }

        this->auto_save_recv_flag = true;
    }
    else
    {
        this->auto_save_recv_flag = false;

        this->auto_save_recv_file->close();
        delete this->auto_save_recv_file;
    }
}

void SerialPortTool::on_pushButton_manule_save_clicked()
{
    char default_str[64];
    bool ok = false;

    QDateTime dateTime = QDateTime::currentDateTime();
    sprintf(default_str, "ManuleSave-%s-%s.txt", ui->comboBox_com_list->currentText().toLocal8Bit().data(),
            dateTime.toString("yyyy-MM-dd_hh-mm-ss").toLocal8Bit().data());
    QString text = QInputDialog::getText(this, tr("保存接收窗口信息"),
                        tr("文件名:"), QLineEdit::Normal, default_str, &ok);
    if(ok && !text.isEmpty())
    {
        this->recv_textEdit_mutex.lock();

        QString txt = ui->textEdit_recv->toPlainText();
        QFile file("./"+text);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.write(txt.toUtf8());
        file.close();

        this->recv_textEdit_mutex.unlock();
    }
}

void SerialPortTool::on_pushButton_open_log_doc_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "打开", "./", "*.txt;;*.*");
    if(!file.isEmpty())
    {
        QProcess *proc = new QProcess();
        proc->start("notepad.exe " + file);
    }
}

void SerialPortTool::on_checkBox_timer_send_stateChanged(int arg1)
{
    char buf[64];

    sprintf(buf, "on_checkBox_timer_send_stateChanged %d\r\n", arg1);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
}

void SerialPortTool::on_comboBox_send_check_func_list_activated(const QString &arg1)
{
    char buf[64];

    sprintf(buf, "on_comboBox_send_check_func_list_activated %s\r\n", arg1.toUtf8().data());
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
}

void SerialPortTool::on_checkBox_crlf_stateChanged(int arg1)
{
    char buf[64];

    sprintf(buf, "on_checkBox_crlf_stateChanged %d\r\n", arg1);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);

    if(arg1 == 2)
    {
        this->crlf_flag = true;
    }
    else
    {
        this->crlf_flag = false;
    }
}

void SerialPortTool::on_checkBox_timestamp_stateChanged(int arg1)
{
    char buf[64];

    sprintf(buf, "on_checkBox_timestamp_stateChanged %d\r\n", arg1);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);

    if(arg1 == 2)
    {
        this->display_time_flag = true;
    }
    else
    {
        this->display_time_flag = false;
    }
}

void SerialPortTool::on_checkBox_hex_send_stateChanged(int arg1)
{
    char buf[64];

    sprintf(buf, "on_checkBox_hex_send_stateChanged %d\r\n", arg1);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);

    if(arg1 == 2)
    {
        this->hex_send_flag = true;
    }
    else
    {
        this->hex_send_flag = false;
    }
}

void SerialPortTool::on_checkBox_hex_recv_stateChanged(int arg1)
{
    char buf[64];

    sprintf(buf, "on_checkBox_hex_recv_stateChanged %d\r\n", arg1);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);

    if(arg1 == 2)
    {
        this->hex_recv_flag = true;
    }
    else
    {
        this->hex_recv_flag = false;
    }
}

void SerialPortTool::on_pushButton_send_str_clicked()
{
    QString str;

    str = ui->textEdit_send->toPlainText();
    this->send_serial(str);
}

void SerialPortTool::on_pushButton_clear_recv_clicked()
{
    this->recv_byte_count = 0;
    this->send_byte_count = 0;

    this->label_tx_status->setText("Tx:0");
    this->label_rx_status->setText("Rx:0");
    ui->textEdit_recv->clear();
}

void SerialPortTool::on_toolButton_data_curve_clicked()
{
    QList<int> list;

    if(this->display_data_curve_flag)
    {
        list << 100 << 0;

        this->display_data_curve_flag = false;
    }
    else
    {
        list << 100 << 100;

        this->display_data_curve_flag = true;
    }

    ui->splitter_curve->setSizes(list);
}

void SerialPortTool::on_toolButton_set_curve_key_clicked()
{
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText("on_toolButton_set_curve_key_clicked\r\n");
    ui->textEdit_recv->moveCursor(QTextCursor::End);
}

void SerialPortTool::on_toolButton_display_expand_cmd_clicked()
{
    QList<int> list;

    if(this->display_cmd_list_flag)
    {
        list << 100 << 0;

        this->display_cmd_list_flag = false;
    }
    else
    {
        list << 100 << 100;

        this->display_cmd_list_flag = true;
    }

    ui->splitter_cmd_list->setSizes(list);
}

void SerialPortTool::on_checkBox_loop_send_stateChanged(int arg1)
{
    char buf[64];

    sprintf(buf, "on_checkBox_hex_send_stateChanged %d\r\n", arg1);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
}

void SerialPortTool::on_pushButton_import_param_clicked()
{
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText("on_pushButton_import_param_clicked\r\n");
    ui->textEdit_recv->moveCursor(QTextCursor::End);
}

void SerialPortTool::on_pushButton_save_param_clicked()
{
    this->set_config_cmd_list();
}

void SerialPortTool::on_pushButton_set_default_clicked()
{
    this->set_config_file_default();
}

void SerialPortTool::on_toolButton_expand_config_serial_clicked()
{
    QList<int> list;

    if(this->display_serial_config_flag)
    {
        list << 0 << 100;

        this->display_serial_config_flag = false;
    }
    else
    {
        list << 100 << 100;

        this->display_serial_config_flag = true;
    }

    ui->splitter_serial_config->setSizes(list);
}

void SerialPortTool::on_toolButton_highlight_key_clicked()
{
    char default_str[512];
    char str[32];
    char *p_str = nullptr;
    uint8_t count = 0;

    this->config_file->beginGroup("highlight_keyword");
    count = 0;
    memset(default_str, 0, sizeof(default_str));

    QStringList kw_list =  this->config_file->childKeys();
    foreach(QString key, kw_list)
    {
        p_str = this->config_file->value(key).toString().toLocal8Bit().data();
        strcat_s(default_str, p_str);
        strcat_s(default_str, "\r\n");
    }
    this->config_file->endGroup();

    bool ok = false;
    QString text = QInputDialog::getMultiLineText(this, tr("请输入需要高亮的关键字分行输入"),
                        tr("高亮关键字列表:"), default_str, &ok);
    if(ok)
    {
        this->keyword_list.clear();
        this->config_file->remove("highlight_keyword");
        this->config_file->beginGroup("highlight_keyword");

        QStringList list = text.split("\n");
        count = 0;
        foreach(QString key, list)
        {
            if(!key.isEmpty())
            {
                this->keyword_list << key;
                sprintf(str, "kw%d", count++);
                this->config_file->setValue(str, key);
            }
        }

        this->config_file->endGroup();
        this->highlight->setTextQueue(this->keyword_list);
    }
}

void SerialPortTool::on_checkBox_window_top_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
    }
    else
    {
        this->setWindowFlags(this->windowFlags() &~ Qt::WindowStaysOnTopHint);
    }

    this->show();
}

void SerialPortTool::on_comboBox_send_protocol_currentTextChanged(const QString &arg1)
{
    char buf[512];

    sprintf(buf, "已选择传输协议: %s\r\n", arg1.toUtf8().data());
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
}

void SerialPortTool::on_comboBox_send_file_currentTextChanged(const QString &arg1)
{
    QString file;

    if(strcmp(arg1.toUtf8().data(), "...") == 0)
    {
        file = QFileDialog::getOpenFileName(this, u8"打开文件", ".", u8"任意文件 (*.*)");
        if(!file.isEmpty())
        {
            ui->comboBox_send_file->addItem(file);
            ui->comboBox_send_file->setCurrentText(file);
            ui->comboBox_send_file->setToolTip(file);
        }
        else
        {
            ui->comboBox_send_file->setCurrentIndex(0);
            ui->comboBox_send_file->setToolTip(ui->comboBox_send_file->currentText());
        }
    }
    else
    {
        ui->comboBox_send_file->setToolTip(arg1);
    }
}

void SerialPortTool::on_pushButton_send_file_clicked()
{
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText("开始发送文件:" + ui->comboBox_send_file->currentText() + "\r\n");
    ui->textEdit_recv->moveCursor(QTextCursor::End);

    if(!this->serial_open_flag)
    {
        QMessageBox::warning(this, "警告", "请打开对应的串口！！！");
        return;
    }

    if(ui->comboBox_send_protocol->currentIndex() == 0)
    {
        QMessageBox::warning(this, "警告", "请选择传输协议！！！");
    }
    else if(strcmp(ui->comboBox_send_protocol->currentText().toLocal8Bit().data(), "ymodem") == 0)
    {
        if(transmitButtonStatus == false)
        {
            serialPort->close();

            ymodemFileTransmit->setFileName(ui->comboBox_send_file->currentText());
            ymodemFileTransmit->setPortName(ui->comboBox_com_list->currentText());
            ymodemFileTransmit->setPortBaudRate(ui->comboBox_baudrate_list->currentText().toInt());

            if(ymodemFileTransmit->startTransmit() == true)
            {
                transmitButtonStatus = true;

                //ui->comButton->setDisabled(true);

                //ui->receiveBrowse->setDisabled(true);
                //ui->receiveButton->setDisabled(true);

                //ui->transmitBrowse->setDisabled(true);
                ui->pushButton_send_file->setText(u8"发送取消");
                this->qProgressBar->setValue(0);
            }
            else
            {
                QMessageBox::warning(this, u8"失败", u8"文件发送失败！", u8"关闭");
            }
        }
        else
        {
            ymodemFileTransmit->stopTransmit();
        }
    }
    else
    {
        QMessageBox::warning(this, "警告", "未定义的传输协议！！！");
    }
}

void SerialPortTool::on_comboBox_recv_directory_currentTextChanged(const QString &arg1)
{
    QString directory;

    if(strcmp(arg1.toUtf8().data(), "...") == 0)
    {
        directory = QFileDialog::getExistingDirectory(this, u8"选择目录", ".", QFileDialog::ShowDirsOnly);
        if(!directory.isEmpty())
        {
            ui->comboBox_recv_directory->addItem(directory);
            ui->comboBox_recv_directory->setCurrentText(directory);
            ui->comboBox_recv_directory->setToolTip(directory);
        }
        else
        {
            ui->comboBox_recv_directory->setCurrentIndex(0);
            ui->comboBox_recv_directory->setToolTip(ui->comboBox_recv_directory->currentText());
        }
    }
    else
    {
        ui->comboBox_recv_directory->setToolTip(arg1);
    }
}

void SerialPortTool::on_pushButton_recv_file_clicked()
{
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText("开始接收文件:" + ui->comboBox_recv_directory->currentText() + "\r\n");
    ui->textEdit_recv->moveCursor(QTextCursor::End);

    if(!this->serial_open_flag)
    {
        QMessageBox::warning(this, "警告", "请打开对应的串口！！！");
        return;
    }

    if(ui->comboBox_send_protocol->currentIndex() == 0)
    {
        QMessageBox::warning(this, "警告", "请选择传输协议！！！");
    }
    else if(strcmp(ui->comboBox_send_protocol->currentText().toLocal8Bit().data(), "ymodem") == 0)
    {
        if(receiveButtonStatus == false)
        {
            serialPort->close();

            ymodemFileReceive->setFilePath(ui->comboBox_recv_directory->currentText());
            ymodemFileReceive->setPortName(ui->comboBox_com_list->currentText());
            ymodemFileReceive->setPortBaudRate(ui->comboBox_baudrate_list->currentText().toInt());

            if(ymodemFileReceive->startReceive() == true)
            {
                receiveButtonStatus = true;

                //ui->comButton->setDisabled(true);

                //ui->transmitBrowse->setDisabled(true);
                //ui->transmitButton->setDisabled(true);

                //ui->receiveBrowse->setDisabled(true);
                ui->pushButton_recv_file->setText(u8"接收取消");
                this->qProgressBar->setValue(0);
            }
            else
            {
                QMessageBox::warning(this, u8"失败", u8"文件接收失败！", u8"关闭");
            }
        }
        else
        {
            ymodemFileReceive->stopReceive();
        }
    }
    else
    {
        QMessageBox::warning(this, "警告", "未定义的传输协议！！！");
    }
}

void SerialPortTool::transmitProgress(int progress)
{
    this->qProgressBar->setValue(progress);
}

void SerialPortTool::receiveProgress(int progress)
{
    this->qProgressBar->setValue(progress);
}

void SerialPortTool::transmitStatus(Ymodem::Status status)
{
    switch(status)
    {
        case YmodemFileTransmit::StatusEstablish:
        {
            break;
        }

        case YmodemFileTransmit::StatusTransmit:
        {
            break;
        }

        case YmodemFileTransmit::StatusFinish:
        {
            transmitButtonStatus = false;

            //ui->comButton->setEnabled(true);

            //ui->receiveBrowse->setEnabled(true);

            //if(ui->receivePath->text().isEmpty() != true)
            {
                //ui->receiveButton->setEnabled(true);
            }

            //ui->transmitBrowse->setEnabled(true);
            ui->pushButton_send_file->setText(u8"发送文件");

            QMessageBox::warning(this, u8"成功", u8"文件发送成功！", u8"关闭");

            break;
        }

        case YmodemFileTransmit::StatusAbort:
        {
            transmitButtonStatus = false;

            //ui->comButton->setEnabled(true);

            //ui->receiveBrowse->setEnabled(true);

            //if(ui->receivePath->text().isEmpty() != true)
            {
                //ui->receiveButton->setEnabled(true);
            }

            //ui->transmitBrowse->setEnabled(true);
            ui->pushButton_send_file->setText(u8"发送文件");

            QMessageBox::warning(this, u8"失败", u8"文件发送失败！", u8"关闭");

            break;
        }

        case YmodemFileTransmit::StatusTimeout:
        {
            transmitButtonStatus = false;

            //ui->comButton->setEnabled(true);

            //ui->receiveBrowse->setEnabled(true);

            //if(ui->receivePath->text().isEmpty() != true)
            {
                //ui->receiveButton->setEnabled(true);
            }

            //ui->transmitBrowse->setEnabled(true);
            ui->pushButton_send_file->setText(u8"发送文件");

            QMessageBox::warning(this, u8"失败", u8"文件发送失败！", u8"关闭");

            break;
        }

        default:
        {
            transmitButtonStatus = false;

            //ui->comButton->setEnabled(true);

            //ui->receiveBrowse->setEnabled(true);

            //if(ui->receivePath->text().isEmpty() != true)
            {
                //ui->receiveButton->setEnabled(true);
            }

            //ui->transmitBrowse->setEnabled(true);
            ui->pushButton_send_file->setText(u8"发送文件");

            QMessageBox::warning(this, u8"失败", u8"文件发送失败！", u8"关闭");
        }
    }
}

void SerialPortTool::receiveStatus(YmodemFileReceive::Status status)
{
    switch(status)
    {
        case YmodemFileReceive::StatusEstablish:
        {
            break;
        }

        case YmodemFileReceive::StatusTransmit:
        {
            break;
        }

        case YmodemFileReceive::StatusFinish:
        {
            receiveButtonStatus = false;

            //ui->comButton->setEnabled(true);

            //ui->transmitBrowse->setEnabled(true);

            //if(ui->transmitPath->text().isEmpty() != true)
            {
                //ui->transmitButton->setEnabled(true);
            }

            //ui->receiveBrowse->setEnabled(true);
            ui->pushButton_recv_file->setText(u8"接收文件");

            QMessageBox::warning(this, u8"成功", u8"文件接收成功！", u8"关闭");

            break;
        }

        case YmodemFileReceive::StatusAbort:
        {
            receiveButtonStatus = false;

            //ui->comButton->setEnabled(true);

           // ui->transmitBrowse->setEnabled(true);

            //if(ui->transmitPath->text().isEmpty() != true)
            {
                //ui->transmitButton->setEnabled(true);
            }

            //ui->receiveBrowse->setEnabled(true);
            ui->pushButton_recv_file->setText(u8"接收文件");

            QMessageBox::warning(this, u8"失败", u8"文件接收失败！", u8"关闭");

            break;
        }

        case YmodemFileReceive::StatusTimeout:
        {
            receiveButtonStatus = false;

            //ui->comButton->setEnabled(true);

            //ui->transmitBrowse->setEnabled(true);

            //if(ui->transmitPath->text().isEmpty() != true)
            {
                //ui->transmitButton->setEnabled(true);
            }

            //ui->receiveBrowse->setEnabled(true);
            ui->pushButton_recv_file->setText(u8"接收文件");

            QMessageBox::warning(this, u8"失败", u8"文件接收失败！", u8"关闭");

            break;
        }

        default:
        {
            receiveButtonStatus = false;

            //ui->comButton->setEnabled(true);

            //ui->transmitBrowse->setEnabled(true);

            //if(ui->transmitPath->text().isEmpty() != true)
            {
                //ui->transmitButton->setEnabled(true);
            }

            //ui->receiveBrowse->setEnabled(true);
            ui->pushButton_recv_file->setText(u8"接收文件");

            QMessageBox::warning(this, u8"失败", u8"文件接收失败！", u8"关闭");
        }
    }
}
