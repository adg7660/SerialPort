#include "serialporttool.h"
#include "ui_serialporttool.h"

#pragma execution_character_set("utf-8")

bool SerialPortTool::open_serial()
{
    this->serial = new QSerialPort;
    this->serial->setPortName(ui->comboBox_com_list->currentText());
    if(!this->serial->open(QIODevice::ReadWrite))
    {
        return false;
    }

#if 1
    this->serial->setBaudRate(ui->comboBox_baudrate_list->currentText().toInt());

    switch(ui->comboBox_data_bit_list->currentIndex())
    {
        case 0:
            this->serial->setDataBits(QSerialPort::Data5);
            break;

        case 1:
            this->serial->setDataBits(QSerialPort::Data6);
            break;

        case 2:
            this->serial->setDataBits(QSerialPort::Data7);
            break;

        case 3:
        default:
            this->serial->setDataBits(QSerialPort::Data8);
    }

    switch(ui->comboBox_check_bit_list->currentIndex())
    {
        case 0:
            this->serial->setParity(QSerialPort::NoParity);
            break;

        case 1:
            this->serial->setParity(QSerialPort::OddParity);
            break;

        case 2:
            this->serial->setParity(QSerialPort::EvenParity);
            break;

        case 3:
            this->serial->setParity(QSerialPort::SpaceParity);
            break;

        case 4:
            this->serial->setParity(QSerialPort::MarkParity);
            break;

        default:
            this->serial->setParity(QSerialPort::NoParity);
    }

    switch(ui->comboBox_stop_bit_list->currentIndex())
    {
        case 0:
            this->serial->setStopBits(QSerialPort::OneStop);
            break;

        case 1:
            this->serial->setStopBits(QSerialPort::OneAndHalfStop);
            break;

        case 2:
            this->serial->setStopBits(QSerialPort::TwoStop);
            break;

        default:
            this->serial->setStopBits(QSerialPort::OneStop);
    }

    switch(ui->comboBox_flow_control_list->currentIndex())
    {
        case 0:
            this->serial->setFlowControl(QSerialPort::NoFlowControl);
            break;

        case 1:
            this->serial->setFlowControl(QSerialPort::HardwareControl);
            break;

        case 2:
            this->serial->setFlowControl(QSerialPort::SoftwareControl);
            break;

        default:
            this->serial->setFlowControl(QSerialPort::NoFlowControl);
    }
#else

    this->serial->setBaudRate(115200);
    this->serial->setDataBits(QSerialPort::Data8);
    this->serial->setParity(QSerialPort::NoParity);
    this->serial->setStopBits(QSerialPort::OneStop);
    this->serial->setFlowControl(QSerialPort::NoFlowControl);
#endif
    connect(this->serial, &QSerialPort::readyRead, this, &SerialPortTool::ReadData);

    return true;
}

void SerialPortTool::close_serial()
{
    this->serial->clear();
    this->serial->close();
    this->serial->deleteLater();
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
    if(this->hex_send_flag == 0)
    {
        if(this->display_time_flag)
        {
            QTime time = QTime::currentTime();
            this->serial->write(("["+time.toString("hh:mm:ss")+"]>>>").toLocal8Bit());
        }

        this->serial->write(str.toLocal8Bit());

        if(this->crlf_flag)
        {
            this->serial->write("\r\n");
        }
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

        this->serial->write(hex_data);
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

    buf += this->serial->readAll();

    if(this->hex_recv_flag == 0)
    {
        //为了保证中文的完整接收，此次不能简单判断是否为空。
        if(buf.endsWith("\r\n"))//!buf.isEmpty())
        {
            str = QString::fromLocal8Bit(buf);

#if 1
            ui->textEdit_recv->moveCursor(QTextCursor::End);
            ui->textEdit_recv->insertPlainText(str);
            ui->textEdit_recv->moveCursor(QTextCursor::End);
#else
            qDebug()<<"-->"<<str;
#endif
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

    for(r=0; r<100; r++)
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

    for(r=1; r<101; r++)
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

SerialPortTool::SerialPortTool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SerialPortTool)
{
    ui->setupUi(this);

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

    this->config_file->beginGroup("network");
    this->config_file->setValue("ip", "192.168.1.1");
    this->config_file->endGroup();

    QString ipstr = this->config_file->value("ip").toString();

    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(ipstr);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
}

void SerialPortTool::setCmdList()
{
    ui->tableWidget_cmd_list->verticalHeader()->setVisible(false);
    ui->tableWidget_cmd_list->horizontalHeader()->setVisible(false);
    ui->tableWidget_cmd_list->setShowGrid(false);

    char str[32];
    for(int r=0; r<101; r++)
    {
        for(int c=0; c<5; c++)
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
#if 0
                        QComboBox *comBox = new QComboBox();
                        comBox->addItem("abc");
                        comBox->addItem("123");

                        ui->tableWidget_cmd_list->setCellWidget(r, c, comBox);
#else
                        QCheckBox *checkBox = new QCheckBox();

                        ui->tableWidget_cmd_list->setCellWidget(r, c, checkBox);
#endif
                    }
                    break;

                case 1:
                    {
                        QLineEdit *lineEdit = new QLineEdit();

                        sprintf(str, "line_%03d", r);
                        lineEdit->setText(str);

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

                        sprintf(str, "%0d", r);
                        lineEdit->setText(str);

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

SerialPortTool::~SerialPortTool()
{
    delete ui;
}

MyPushButton::~MyPushButton()
{
    //delete ui;
}

void SerialPortTool::on_comboBox_baudrate_list_activated(const QString &arg1)
{
    char buf[64];

    sprintf(buf, "on_comboBox_baudrate_list_activated %s\r\n", arg1.toUtf8().data());
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
}

void SerialPortTool::on_comboBox_data_bit_list_activated(const QString &arg1)
{
    char buf[64];

    sprintf(buf, "on_comboBox_data_bit_list_activated %s\r\n", arg1.toUtf8().data());
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
}

void SerialPortTool::on_comboBox_stop_bit_list_activated(const QString &arg1)
{
    char buf[64];

    sprintf(buf, "on_comboBox_stop_bit_list_activated %s\r\n", arg1.toUtf8().data());
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
}

void SerialPortTool::on_comboBox_check_bit_list_activated(const QString &arg1)
{
    char buf[64];

    sprintf(buf, "on_comboBox_check_bit_list_activated %s\r\n", arg1.toUtf8().data());
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
}

void SerialPortTool::on_comboBox_flow_control_list_activated(const QString &arg1)
{
    char buf[64];

    sprintf(buf, "on_comboBox_flow_control_list_activated %s\r\n", arg1.toUtf8().data());
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
}

void SerialPortTool::on_pushButton_open_serial_clicked()
{
    if(this->serial_open_flag == 0)
    {
        if(this->open_serial())
        {
            this->serial_open_flag = 1;
            ui->pushButton_open_serial->setText("关闭串口");
        }
        else
        {
            QMessageBox::warning(this, "警告", "***串口已被其他程序打开***");
        }
    }
    else
    {
        this->serial_open_flag = 0;
        ui->pushButton_open_serial->setText("打开串口");
        this->close_serial();
    }
}

void SerialPortTool::on_pushButton_refresh_serial_clicked()
{
    if(this->serial_open_flag == 1)
    {
        this->serial_open_flag = 0;
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
    char buf[64];

    sprintf(buf, "on_checkBox_autosave_stateChanged %d\r\n", arg1);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
}

void SerialPortTool::on_toolButton_highlight_key_triggered(QAction *arg1)
{
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText("on_toolButton_highlight_key_triggered\r\n");
    ui->textEdit_recv->moveCursor(QTextCursor::End);
}

void SerialPortTool::on_pushButton_manule_save_clicked()
{
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText("on_pushButton_manule_save_clicked\r\n");
    ui->textEdit_recv->moveCursor(QTextCursor::End);
}

void SerialPortTool::on_pushButton_open_log_doc_clicked()
{
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText("on_pushButton_open_log_doc_clicked\r\n");
    ui->textEdit_recv->moveCursor(QTextCursor::End);
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

void SerialPortTool::on_comboBox_send_file_currentIndexChanged(int index)
{
    char buf[64];

    sprintf(buf, "on_comboBox_send_file_currentIndexChanged %d\r\n", index);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
}

void SerialPortTool::on_comboBox_send_protocol_currentIndexChanged(int index)
{
    char buf[64];

    sprintf(buf, "on_comboBox_send_protocol_currentIndexChanged %d\r\n", index);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText(buf);
    ui->textEdit_recv->moveCursor(QTextCursor::End);
}

void SerialPortTool::on_pushButton_send_file_clicked()
{
    ui->textEdit_recv->moveCursor(QTextCursor::End);
    ui->textEdit_recv->insertPlainText("on_pushButton_send_file_clicked\r\n");
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
        this->crlf_flag = 1;
    }
    else
    {
        this->crlf_flag = 0;
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
        this->display_time_flag = 1;
    }
    else
    {
        this->display_time_flag = 0;
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
        this->hex_send_flag = 1;
    }
    else
    {
        this->hex_send_flag = 0;
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
        this->hex_recv_flag = 1;
    }
    else
    {
        this->hex_recv_flag = 0;
    }
}

void SerialPortTool::on_pushButton_send_str_clicked()
{
    QString str;

    if(this->serial_open_flag == 1)
    {
        str = ui->textEdit_send->toPlainText();
        this->send_serial(str);
    }
    else
    {
        QMessageBox::warning(this, "警告", "请打开对应的串口！！！");
    }
}

void SerialPortTool::on_pushButton_clear_recv_clicked()
{
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
