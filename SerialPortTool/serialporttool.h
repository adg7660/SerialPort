#ifndef SERIALPORTTOOL_H
#define SERIALPORTTOOL_H

#include <string.h>
#include <QMainWindow>
#include <QMessageBox>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
#include <QMouseEvent>
#include <QInputDialog>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSettings>
#include <QMutex>
#include <QStatusBar>
#include <QProgressBar>
#include <qapplication.h>

#include "qcustomplot/qcustomplot.h"
#include "highlight_keyword/highlight_keyword.h"
#include "ymodem/YmodemFileTransmit.h"
#include "ymodem/YmodemFileReceive.h"

namespace Ui {
class SerialPortTool;
}

#define CMD_LIST_ROW    100
#define CMD_LIST_COL    5

class SerialPortTool : public QMainWindow
{
    Q_OBJECT

public:
    explicit SerialPortTool(QWidget *parent = nullptr);
    ~SerialPortTool();

    bool display_cmd_list_flag;
    bool display_data_curve_flag;
    bool display_serial_config_flag;
    QTimer *timer = nullptr;
    bool crlf_flag = false;
    bool display_time_flag = false;
    bool hex_send_flag = false;
    bool hex_recv_flag = false;
    bool serial_open_flag = false;
    bool auto_save_recv_flag = false;
    QString demoName;

    QString config_file_name;
    QSettings *config_file = nullptr;
    Highlighter *highlight = nullptr;
    QStringList keyword_list;
    QFile *auto_save_recv_file = nullptr;
    int recv_byte_count = 0;
    int send_byte_count = 0;
    QProgressBar *qProgressBar = nullptr;
    QLabel *label_tx_status = nullptr;
    QLabel *label_rx_status = nullptr;

    QMutex recv_textEdit_mutex;

    void setCmdList();
    bool open_serial();
    void close_serial();
    void refresh_serial();
    void send_serial(QString str);
    void setupQuadraticDemo(QCustomPlot *customPlot);

    void set_config_file_default();
    void set_config_cmd_list();
    void ReadCmdList();

private slots:
    void on_comboBox_baudrate_list_activated(const QString &arg1);

    void on_comboBox_data_bit_list_activated(const QString &arg1);

    void on_comboBox_stop_bit_list_activated(const QString &arg1);

    void on_comboBox_check_bit_list_activated(const QString &arg1);

    void on_comboBox_flow_control_list_activated(const QString &arg1);

    void on_pushButton_open_serial_clicked();

    void on_pushButton_refresh_serial_clicked();

    void on_checkBox_rts_stateChanged(int arg1);

    void on_checkBox_dtr_stateChanged(int arg1);

    void on_checkBox_autosave_stateChanged(int arg1);

    void on_pushButton_manule_save_clicked();

    void on_pushButton_open_log_doc_clicked();

    void on_checkBox_timer_send_stateChanged(int arg1);

    void on_comboBox_send_check_func_list_activated(const QString &arg1);

    void on_comboBox_send_file_currentIndexChanged(int index);

    void on_comboBox_send_protocol_currentIndexChanged(int index);

    void on_pushButton_send_file_clicked();

    void on_checkBox_crlf_stateChanged(int arg1);

    void on_checkBox_timestamp_stateChanged(int arg1);

    void on_checkBox_hex_send_stateChanged(int arg1);

    void on_checkBox_hex_recv_stateChanged(int arg1);

    void on_pushButton_send_str_clicked();

    void on_pushButton_clear_recv_clicked();

    void OnBtnLeftClicked();
    void OnBtnRightClicked();
    void onTimerOut();
    void ReadData();
    void onCurrentLineHighLight();

    void on_toolButton_data_curve_clicked();

    void on_toolButton_set_curve_key_clicked();

    void on_toolButton_display_expand_cmd_clicked();

    void on_checkBox_loop_send_stateChanged(int arg1);

    void on_pushButton_import_param_clicked();

    void on_pushButton_save_param_clicked();

    void on_pushButton_set_default_clicked();

    void on_toolButton_expand_config_serial_clicked();

    void on_toolButton_highlight_key_clicked();

    void on_checkBox_window_top_stateChanged(int arg1);

private:
    Ui::SerialPortTool *ui;

    QSerialPort *serialPort = nullptr;
    YmodemFileTransmit *ymodemFileTransmit = nullptr;
    YmodemFileReceive *ymodemFileReceive = nullptr;

    bool transmitButtonStatus;
    bool receiveButtonStatus;
};

class MyPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit MyPushButton(QWidget *parent = nullptr);
    ~MyPushButton();

    virtual void mouseReleaseEvent(QMouseEvent *e);

signals:
    void leftButtonClicked();
    void rightButtonClicked();

private slots:
};

#endif // SERIALPORTTOOL_H
