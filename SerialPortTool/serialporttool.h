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
#include <qapplication.h>

#include "qcustomplot.h"
#include "highlight_keyword.h"

namespace Ui {
class SerialPortTool;
}

class SerialPortTool : public QMainWindow
{
    Q_OBJECT

public:
    explicit SerialPortTool(QWidget *parent = nullptr);
    ~SerialPortTool();

    bool display_cmd_list_flag;
    bool display_data_curve_flag;
    bool display_serial_config_flag;
    QTimer *timer;
    QSerialPort *serial;
    uint8_t crlf_flag = 0;
    uint8_t display_time_flag = 0;
    uint8_t hex_send_flag = 0;
    uint8_t hex_recv_flag = 0;
    uint8_t serial_open_flag = 0;
    QString demoName;

    QString config_file_name;
    QSettings *config_file;
    Highlighter *highlight;
    QStringList keyword_list;

    void setCmdList();
    bool open_serial();
    void close_serial();
    void refresh_serial();
    void send_serial(QString str);
    void setupQuadraticDemo(QCustomPlot *customPlot);

    void set_config_file_default();
    void set_config_cmd_list();

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

private:
    Ui::SerialPortTool *ui;
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
