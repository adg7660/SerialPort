/********************************************************************************
** Form generated from reading UI file 'serialporttool.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALPORTTOOL_H
#define UI_SERIALPORTTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_SerialPortTool
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_22;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_com;
    QComboBox *comboBox_com_list;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_baudrate;
    QComboBox *comboBox_baudrate_list;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_data_bit;
    QComboBox *comboBox_data_bit_list;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_stop_bit;
    QComboBox *comboBox_stop_bit_list;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_check_bit;
    QComboBox *comboBox_check_bit_list;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_flow_control;
    QComboBox *comboBox_flow_control_list;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_open_serial;
    QPushButton *pushButton_refresh_serial;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_4;
    QLCDNumber *lcdNumber_time;
    QHBoxLayout *horizontalLayout_17;
    QCheckBox *checkBox_autosave;
    QCheckBox *checkBox_rts;
    QCheckBox *checkBox_dtr;
    QHBoxLayout *horizontalLayout_18;
    QHBoxLayout *horizontalLayout_19;
    QPushButton *pushButton_manule_save;
    QPushButton *pushButton_open_log_doc;
    QToolButton *toolButton_highlight_key;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *checkBox_timer_send;
    QLineEdit *lineEdit_timer_send_interval;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_send_check;
    QComboBox *comboBox_send_check_func_list;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QLineEdit *lineEdit_start_bit;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_11;
    QLineEdit *lineEdit_end_bit;
    QLabel *label_12;
    QSplitter *splitter_cmd_list;
    QSplitter *splitter_curve;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *textEdit_recv;
    QHBoxLayout *horizontalLayout_16;
    QComboBox *comboBox_send_file;
    QComboBox *comboBox_send_protocol;
    QPushButton *pushButton_send_file;
    QHBoxLayout *horizontalLayout_21;
    QTextEdit *textEdit_send;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_15;
    QToolButton *toolButton_data_curve;
    QToolButton *toolButton_set_curve;
    QToolButton *toolButton_display_expand_cmd;
    QHBoxLayout *horizontalLayout_12;
    QCheckBox *checkBox_crlf;
    QCheckBox *checkBox_timestamp;
    QHBoxLayout *horizontalLayout_13;
    QCheckBox *checkBox_hex_send;
    QCheckBox *checkBox_hex_recv;
    QHBoxLayout *horizontalLayout_14;
    QPushButton *pushButton_send_str;
    QPushButton *pushButton_clear_recv;
    QCustomPlot *customplot_data_curve;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_20;
    QCheckBox *checkBox_loop_send;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_import_param;
    QPushButton *pushButton_save_param;
    QPushButton *pushButton_set_default;
    QTableWidget *tableWidget_cmd_list;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SerialPortTool)
    {
        if (SerialPortTool->objectName().isEmpty())
            SerialPortTool->setObjectName(QStringLiteral("SerialPortTool"));
        SerialPortTool->resize(1189, 751);
        centralWidget = new QWidget(SerialPortTool);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_22 = new QHBoxLayout(centralWidget);
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_com = new QLabel(centralWidget);
        label_com->setObjectName(QStringLiteral("label_com"));

        horizontalLayout->addWidget(label_com);

        comboBox_com_list = new QComboBox(centralWidget);
        comboBox_com_list->setObjectName(QStringLiteral("comboBox_com_list"));

        horizontalLayout->addWidget(comboBox_com_list);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 2);

        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_baudrate = new QLabel(centralWidget);
        label_baudrate->setObjectName(QStringLiteral("label_baudrate"));

        horizontalLayout_2->addWidget(label_baudrate);

        comboBox_baudrate_list = new QComboBox(centralWidget);
        comboBox_baudrate_list->addItem(QString());
        comboBox_baudrate_list->addItem(QString());
        comboBox_baudrate_list->addItem(QString());
        comboBox_baudrate_list->addItem(QString());
        comboBox_baudrate_list->addItem(QString());
        comboBox_baudrate_list->addItem(QString());
        comboBox_baudrate_list->setObjectName(QStringLiteral("comboBox_baudrate_list"));

        horizontalLayout_2->addWidget(comboBox_baudrate_list);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 2);

        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_data_bit = new QLabel(centralWidget);
        label_data_bit->setObjectName(QStringLiteral("label_data_bit"));

        horizontalLayout_3->addWidget(label_data_bit);

        comboBox_data_bit_list = new QComboBox(centralWidget);
        comboBox_data_bit_list->addItem(QString());
        comboBox_data_bit_list->addItem(QString());
        comboBox_data_bit_list->addItem(QString());
        comboBox_data_bit_list->addItem(QString());
        comboBox_data_bit_list->setObjectName(QStringLiteral("comboBox_data_bit_list"));

        horizontalLayout_3->addWidget(comboBox_data_bit_list);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 2);

        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_stop_bit = new QLabel(centralWidget);
        label_stop_bit->setObjectName(QStringLiteral("label_stop_bit"));

        horizontalLayout_4->addWidget(label_stop_bit);

        comboBox_stop_bit_list = new QComboBox(centralWidget);
        comboBox_stop_bit_list->addItem(QString());
        comboBox_stop_bit_list->addItem(QString());
        comboBox_stop_bit_list->addItem(QString());
        comboBox_stop_bit_list->setObjectName(QStringLiteral("comboBox_stop_bit_list"));

        horizontalLayout_4->addWidget(comboBox_stop_bit_list);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 2);

        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_check_bit = new QLabel(centralWidget);
        label_check_bit->setObjectName(QStringLiteral("label_check_bit"));

        horizontalLayout_5->addWidget(label_check_bit);

        comboBox_check_bit_list = new QComboBox(centralWidget);
        comboBox_check_bit_list->addItem(QString());
        comboBox_check_bit_list->addItem(QString());
        comboBox_check_bit_list->addItem(QString());
        comboBox_check_bit_list->setObjectName(QStringLiteral("comboBox_check_bit_list"));

        horizontalLayout_5->addWidget(comboBox_check_bit_list);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 2);

        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_flow_control = new QLabel(centralWidget);
        label_flow_control->setObjectName(QStringLiteral("label_flow_control"));

        horizontalLayout_6->addWidget(label_flow_control);

        comboBox_flow_control_list = new QComboBox(centralWidget);
        comboBox_flow_control_list->addItem(QString());
        comboBox_flow_control_list->addItem(QString());
        comboBox_flow_control_list->addItem(QString());
        comboBox_flow_control_list->addItem(QString());
        comboBox_flow_control_list->setObjectName(QStringLiteral("comboBox_flow_control_list"));

        horizontalLayout_6->addWidget(comboBox_flow_control_list);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 2);

        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalSpacer_2 = new QSpacerItem(64, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_2);

        pushButton_open_serial = new QPushButton(centralWidget);
        pushButton_open_serial->setObjectName(QStringLiteral("pushButton_open_serial"));
        pushButton_open_serial->setMaximumSize(QSize(64, 16777215));

        horizontalLayout_11->addWidget(pushButton_open_serial);

        pushButton_refresh_serial = new QPushButton(centralWidget);
        pushButton_refresh_serial->setObjectName(QStringLiteral("pushButton_refresh_serial"));
        pushButton_refresh_serial->setMaximumSize(QSize(64, 16777215));

        horizontalLayout_11->addWidget(pushButton_refresh_serial);

        horizontalLayout_11->setStretch(0, 6);
        horizontalLayout_11->setStretch(1, 1);
        horizontalLayout_11->setStretch(2, 1);

        verticalLayout_3->addLayout(horizontalLayout_11);


        verticalLayout_6->addLayout(verticalLayout_3);

        verticalSpacer = new QSpacerItem(20, 168, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetFixedSize);
        lcdNumber_time = new QLCDNumber(centralWidget);
        lcdNumber_time->setObjectName(QStringLiteral("lcdNumber_time"));
        lcdNumber_time->setMinimumSize(QSize(0, 24));
        lcdNumber_time->setDigitCount(19);
        lcdNumber_time->setSegmentStyle(QLCDNumber::Flat);

        verticalLayout_4->addWidget(lcdNumber_time);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        checkBox_autosave = new QCheckBox(centralWidget);
        checkBox_autosave->setObjectName(QStringLiteral("checkBox_autosave"));

        horizontalLayout_17->addWidget(checkBox_autosave);

        checkBox_rts = new QCheckBox(centralWidget);
        checkBox_rts->setObjectName(QStringLiteral("checkBox_rts"));

        horizontalLayout_17->addWidget(checkBox_rts);

        checkBox_dtr = new QCheckBox(centralWidget);
        checkBox_dtr->setObjectName(QStringLiteral("checkBox_dtr"));

        horizontalLayout_17->addWidget(checkBox_dtr);


        verticalLayout_4->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));

        verticalLayout_4->addLayout(horizontalLayout_18);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        pushButton_manule_save = new QPushButton(centralWidget);
        pushButton_manule_save->setObjectName(QStringLiteral("pushButton_manule_save"));
        pushButton_manule_save->setMaximumSize(QSize(66, 16777215));

        horizontalLayout_19->addWidget(pushButton_manule_save);

        pushButton_open_log_doc = new QPushButton(centralWidget);
        pushButton_open_log_doc->setObjectName(QStringLiteral("pushButton_open_log_doc"));
        pushButton_open_log_doc->setMaximumSize(QSize(66, 16777215));

        horizontalLayout_19->addWidget(pushButton_open_log_doc);

        toolButton_highlight_key = new QToolButton(centralWidget);
        toolButton_highlight_key->setObjectName(QStringLiteral("toolButton_highlight_key"));

        horizontalLayout_19->addWidget(toolButton_highlight_key);


        verticalLayout_4->addLayout(horizontalLayout_19);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        checkBox_timer_send = new QCheckBox(centralWidget);
        checkBox_timer_send->setObjectName(QStringLiteral("checkBox_timer_send"));

        horizontalLayout_7->addWidget(checkBox_timer_send);

        lineEdit_timer_send_interval = new QLineEdit(centralWidget);
        lineEdit_timer_send_interval->setObjectName(QStringLiteral("lineEdit_timer_send_interval"));
        lineEdit_timer_send_interval->setMaximumSize(QSize(48, 16777215));

        horizontalLayout_7->addWidget(lineEdit_timer_send_interval);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_send_check = new QLabel(centralWidget);
        label_send_check->setObjectName(QStringLiteral("label_send_check"));
        label_send_check->setMaximumSize(QSize(64, 16777215));

        horizontalLayout_8->addWidget(label_send_check);

        comboBox_send_check_func_list = new QComboBox(centralWidget);
        comboBox_send_check_func_list->addItem(QString());
        comboBox_send_check_func_list->addItem(QString());
        comboBox_send_check_func_list->addItem(QString());
        comboBox_send_check_func_list->addItem(QString());
        comboBox_send_check_func_list->addItem(QString());
        comboBox_send_check_func_list->setObjectName(QStringLiteral("comboBox_send_check_func_list"));

        horizontalLayout_8->addWidget(comboBox_send_check_func_list);

        horizontalLayout_8->setStretch(0, 1);
        horizontalLayout_8->setStretch(1, 2);

        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_9->addWidget(label_9);

        lineEdit_start_bit = new QLineEdit(centralWidget);
        lineEdit_start_bit->setObjectName(QStringLiteral("lineEdit_start_bit"));
        lineEdit_start_bit->setMaximumSize(QSize(48, 16777215));

        horizontalLayout_9->addWidget(lineEdit_start_bit);

        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_9->addWidget(label_10);


        verticalLayout_4->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_10->addWidget(label_11);

        lineEdit_end_bit = new QLineEdit(centralWidget);
        lineEdit_end_bit->setObjectName(QStringLiteral("lineEdit_end_bit"));
        lineEdit_end_bit->setMaximumSize(QSize(48, 16777215));

        horizontalLayout_10->addWidget(lineEdit_end_bit);

        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_10->addWidget(label_12);


        verticalLayout_4->addLayout(horizontalLayout_10);


        verticalLayout_6->addLayout(verticalLayout_4);


        horizontalLayout_22->addLayout(verticalLayout_6);

        splitter_cmd_list = new QSplitter(centralWidget);
        splitter_cmd_list->setObjectName(QStringLiteral("splitter_cmd_list"));
        splitter_cmd_list->setOrientation(Qt::Horizontal);
        splitter_curve = new QSplitter(splitter_cmd_list);
        splitter_curve->setObjectName(QStringLiteral("splitter_curve"));
        splitter_curve->setOrientation(Qt::Vertical);
        widget = new QWidget(splitter_curve);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        textEdit_recv = new QTextEdit(widget);
        textEdit_recv->setObjectName(QStringLiteral("textEdit_recv"));

        verticalLayout_2->addWidget(textEdit_recv);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(2);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        comboBox_send_file = new QComboBox(widget);
        comboBox_send_file->addItem(QString());
        comboBox_send_file->addItem(QString());
        comboBox_send_file->setObjectName(QStringLiteral("comboBox_send_file"));

        horizontalLayout_16->addWidget(comboBox_send_file);

        comboBox_send_protocol = new QComboBox(widget);
        comboBox_send_protocol->addItem(QString());
        comboBox_send_protocol->addItem(QString());
        comboBox_send_protocol->setObjectName(QStringLiteral("comboBox_send_protocol"));

        horizontalLayout_16->addWidget(comboBox_send_protocol);

        pushButton_send_file = new QPushButton(widget);
        pushButton_send_file->setObjectName(QStringLiteral("pushButton_send_file"));

        horizontalLayout_16->addWidget(pushButton_send_file);

        horizontalLayout_16->setStretch(0, 6);
        horizontalLayout_16->setStretch(1, 2);
        horizontalLayout_16->setStretch(2, 1);

        verticalLayout_2->addLayout(horizontalLayout_16);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(2);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        horizontalLayout_21->setSizeConstraint(QLayout::SetFixedSize);
        textEdit_send = new QTextEdit(widget);
        textEdit_send->setObjectName(QStringLiteral("textEdit_send"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit_send->sizePolicy().hasHeightForWidth());
        textEdit_send->setSizePolicy(sizePolicy);
        textEdit_send->setMinimumSize(QSize(0, 94));
        textEdit_send->setMaximumSize(QSize(16777215, 94));

        horizontalLayout_21->addWidget(textEdit_send);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(2);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        horizontalLayout_15->setSizeConstraint(QLayout::SetFixedSize);
        toolButton_data_curve = new QToolButton(widget);
        toolButton_data_curve->setObjectName(QStringLiteral("toolButton_data_curve"));

        horizontalLayout_15->addWidget(toolButton_data_curve);

        toolButton_set_curve = new QToolButton(widget);
        toolButton_set_curve->setObjectName(QStringLiteral("toolButton_set_curve"));

        horizontalLayout_15->addWidget(toolButton_set_curve);

        toolButton_display_expand_cmd = new QToolButton(widget);
        toolButton_display_expand_cmd->setObjectName(QStringLiteral("toolButton_display_expand_cmd"));

        horizontalLayout_15->addWidget(toolButton_display_expand_cmd);


        verticalLayout->addLayout(horizontalLayout_15);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(2);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_12->setSizeConstraint(QLayout::SetFixedSize);
        checkBox_crlf = new QCheckBox(widget);
        checkBox_crlf->setObjectName(QStringLiteral("checkBox_crlf"));
        checkBox_crlf->setMinimumSize(QSize(80, 20));
        checkBox_crlf->setMaximumSize(QSize(80, 24));

        horizontalLayout_12->addWidget(checkBox_crlf);

        checkBox_timestamp = new QCheckBox(widget);
        checkBox_timestamp->setObjectName(QStringLiteral("checkBox_timestamp"));
        checkBox_timestamp->setMinimumSize(QSize(80, 20));
        checkBox_timestamp->setMaximumSize(QSize(80, 24));

        horizontalLayout_12->addWidget(checkBox_timestamp);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(2);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalLayout_13->setSizeConstraint(QLayout::SetFixedSize);
        checkBox_hex_send = new QCheckBox(widget);
        checkBox_hex_send->setObjectName(QStringLiteral("checkBox_hex_send"));
        checkBox_hex_send->setMinimumSize(QSize(80, 20));
        checkBox_hex_send->setMaximumSize(QSize(80, 24));

        horizontalLayout_13->addWidget(checkBox_hex_send);

        checkBox_hex_recv = new QCheckBox(widget);
        checkBox_hex_recv->setObjectName(QStringLiteral("checkBox_hex_recv"));
        checkBox_hex_recv->setMinimumSize(QSize(80, 20));
        checkBox_hex_recv->setMaximumSize(QSize(80, 24));

        horizontalLayout_13->addWidget(checkBox_hex_recv);


        verticalLayout->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(2);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalLayout_14->setSizeConstraint(QLayout::SetFixedSize);
        pushButton_send_str = new QPushButton(widget);
        pushButton_send_str->setObjectName(QStringLiteral("pushButton_send_str"));
        pushButton_send_str->setMinimumSize(QSize(80, 20));
        pushButton_send_str->setMaximumSize(QSize(80, 24));

        horizontalLayout_14->addWidget(pushButton_send_str);

        pushButton_clear_recv = new QPushButton(widget);
        pushButton_clear_recv->setObjectName(QStringLiteral("pushButton_clear_recv"));
        pushButton_clear_recv->setMinimumSize(QSize(80, 20));
        pushButton_clear_recv->setMaximumSize(QSize(80, 24));

        horizontalLayout_14->addWidget(pushButton_clear_recv);


        verticalLayout->addLayout(horizontalLayout_14);


        horizontalLayout_21->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_21);

        splitter_curve->addWidget(widget);
        customplot_data_curve = new QCustomPlot(splitter_curve);
        customplot_data_curve->setObjectName(QStringLiteral("customplot_data_curve"));
        customplot_data_curve->setMinimumSize(QSize(0, 128));
        customplot_data_curve->setMaximumSize(QSize(16777215, 512));
        splitter_curve->addWidget(customplot_data_curve);
        splitter_cmd_list->addWidget(splitter_curve);
        widget1 = new QWidget(splitter_cmd_list);
        widget1->setObjectName(QStringLiteral("widget1"));
        verticalLayout_7 = new QVBoxLayout(widget1);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        horizontalLayout_20->setSizeConstraint(QLayout::SetFixedSize);
        checkBox_loop_send = new QCheckBox(widget1);
        checkBox_loop_send->setObjectName(QStringLiteral("checkBox_loop_send"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(checkBox_loop_send->sizePolicy().hasHeightForWidth());
        checkBox_loop_send->setSizePolicy(sizePolicy1);
        checkBox_loop_send->setMinimumSize(QSize(64, 0));
        checkBox_loop_send->setMaximumSize(QSize(85, 16777215));

        horizontalLayout_20->addWidget(checkBox_loop_send);

        horizontalSpacer = new QSpacerItem(128, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_20->addItem(horizontalSpacer);

        pushButton_import_param = new QPushButton(widget1);
        pushButton_import_param->setObjectName(QStringLiteral("pushButton_import_param"));
        sizePolicy1.setHeightForWidth(pushButton_import_param->sizePolicy().hasHeightForWidth());
        pushButton_import_param->setSizePolicy(sizePolicy1);
        pushButton_import_param->setMinimumSize(QSize(64, 0));
        pushButton_import_param->setMaximumSize(QSize(64, 16777215));

        horizontalLayout_20->addWidget(pushButton_import_param);

        pushButton_save_param = new QPushButton(widget1);
        pushButton_save_param->setObjectName(QStringLiteral("pushButton_save_param"));
        sizePolicy1.setHeightForWidth(pushButton_save_param->sizePolicy().hasHeightForWidth());
        pushButton_save_param->setSizePolicy(sizePolicy1);
        pushButton_save_param->setMinimumSize(QSize(64, 0));
        pushButton_save_param->setMaximumSize(QSize(64, 16777215));

        horizontalLayout_20->addWidget(pushButton_save_param);

        pushButton_set_default = new QPushButton(widget1);
        pushButton_set_default->setObjectName(QStringLiteral("pushButton_set_default"));
        sizePolicy1.setHeightForWidth(pushButton_set_default->sizePolicy().hasHeightForWidth());
        pushButton_set_default->setSizePolicy(sizePolicy1);
        pushButton_set_default->setMinimumSize(QSize(64, 0));
        pushButton_set_default->setMaximumSize(QSize(64, 16777215));

        horizontalLayout_20->addWidget(pushButton_set_default);

        horizontalLayout_20->setStretch(0, 1);
        horizontalLayout_20->setStretch(1, 1);
        horizontalLayout_20->setStretch(2, 1);
        horizontalLayout_20->setStretch(3, 1);
        horizontalLayout_20->setStretch(4, 1);

        verticalLayout_7->addLayout(horizontalLayout_20);

        tableWidget_cmd_list = new QTableWidget(widget1);
        if (tableWidget_cmd_list->columnCount() < 5)
            tableWidget_cmd_list->setColumnCount(5);
        if (tableWidget_cmd_list->rowCount() < 101)
            tableWidget_cmd_list->setRowCount(101);
        tableWidget_cmd_list->setObjectName(QStringLiteral("tableWidget_cmd_list"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tableWidget_cmd_list->sizePolicy().hasHeightForWidth());
        tableWidget_cmd_list->setSizePolicy(sizePolicy2);
        tableWidget_cmd_list->setMinimumSize(QSize(435, 0));
        tableWidget_cmd_list->setMaximumSize(QSize(435, 16777215));
        tableWidget_cmd_list->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget_cmd_list->setRowCount(101);
        tableWidget_cmd_list->setColumnCount(5);
        tableWidget_cmd_list->verticalHeader()->setDefaultSectionSize(26);

        verticalLayout_7->addWidget(tableWidget_cmd_list);

        verticalLayout_7->setStretch(0, 1);
        verticalLayout_7->setStretch(1, 50);
        splitter_cmd_list->addWidget(widget1);

        horizontalLayout_22->addWidget(splitter_cmd_list);

        horizontalLayout_22->setStretch(0, 1);
        horizontalLayout_22->setStretch(1, 30);
        SerialPortTool->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SerialPortTool);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1189, 26));
        SerialPortTool->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SerialPortTool);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SerialPortTool->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SerialPortTool);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SerialPortTool->setStatusBar(statusBar);

        retranslateUi(SerialPortTool);

        QMetaObject::connectSlotsByName(SerialPortTool);
    } // setupUi

    void retranslateUi(QMainWindow *SerialPortTool)
    {
        SerialPortTool->setWindowTitle(QApplication::translate("SerialPortTool", "SerialPortTool", nullptr));
        label_com->setText(QApplication::translate("SerialPortTool", "\347\253\257\345\217\243\345\217\267", nullptr));
        label_baudrate->setText(QApplication::translate("SerialPortTool", "\346\263\242\347\211\271\347\216\207", nullptr));
        comboBox_baudrate_list->setItemText(0, QApplication::translate("SerialPortTool", "1200", nullptr));
        comboBox_baudrate_list->setItemText(1, QApplication::translate("SerialPortTool", "2400", nullptr));
        comboBox_baudrate_list->setItemText(2, QApplication::translate("SerialPortTool", "4800", nullptr));
        comboBox_baudrate_list->setItemText(3, QApplication::translate("SerialPortTool", "9600", nullptr));
        comboBox_baudrate_list->setItemText(4, QApplication::translate("SerialPortTool", "115200", nullptr));
        comboBox_baudrate_list->setItemText(5, QApplication::translate("SerialPortTool", "921600", nullptr));

        label_data_bit->setText(QApplication::translate("SerialPortTool", "\346\225\260\346\215\256\344\275\215", nullptr));
        comboBox_data_bit_list->setItemText(0, QApplication::translate("SerialPortTool", "5 bit", nullptr));
        comboBox_data_bit_list->setItemText(1, QApplication::translate("SerialPortTool", "6 bit", nullptr));
        comboBox_data_bit_list->setItemText(2, QApplication::translate("SerialPortTool", "7 bit", nullptr));
        comboBox_data_bit_list->setItemText(3, QApplication::translate("SerialPortTool", "8 bit", nullptr));

        label_stop_bit->setText(QApplication::translate("SerialPortTool", "\345\201\234\346\255\242\344\275\215", nullptr));
        comboBox_stop_bit_list->setItemText(0, QApplication::translate("SerialPortTool", "1 bit", nullptr));
        comboBox_stop_bit_list->setItemText(1, QApplication::translate("SerialPortTool", "1.5 bit", nullptr));
        comboBox_stop_bit_list->setItemText(2, QApplication::translate("SerialPortTool", "2 bit", nullptr));

        label_check_bit->setText(QApplication::translate("SerialPortTool", "\346\240\241\351\252\214\344\275\215", nullptr));
        comboBox_check_bit_list->setItemText(0, QApplication::translate("SerialPortTool", "\346\227\240\346\240\241\351\252\214", nullptr));
        comboBox_check_bit_list->setItemText(1, QApplication::translate("SerialPortTool", "\345\245\207\346\240\241\351\252\214", nullptr));
        comboBox_check_bit_list->setItemText(2, QApplication::translate("SerialPortTool", "\345\201\266\346\240\241\351\252\214", nullptr));

        label_flow_control->setText(QApplication::translate("SerialPortTool", "\346\265\201\346\216\247\345\210\266", nullptr));
        comboBox_flow_control_list->setItemText(0, QApplication::translate("SerialPortTool", "\346\227\240\346\265\201\346\216\247\345\210\266", nullptr));
        comboBox_flow_control_list->setItemText(1, QApplication::translate("SerialPortTool", "\347\241\254\344\273\266\346\265\201\346\216\247\345\210\266", nullptr));
        comboBox_flow_control_list->setItemText(2, QApplication::translate("SerialPortTool", "\350\275\257\344\273\266\346\265\201\346\216\247\345\210\266", nullptr));
        comboBox_flow_control_list->setItemText(3, QApplication::translate("SerialPortTool", "\350\207\252\345\256\232\344\271\211", nullptr));

        pushButton_open_serial->setText(QApplication::translate("SerialPortTool", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        pushButton_refresh_serial->setText(QApplication::translate("SerialPortTool", "\345\210\267\346\226\260\344\270\262\345\217\243", nullptr));
        checkBox_autosave->setText(QApplication::translate("SerialPortTool", "\350\207\252\345\212\250\344\277\235\345\255\230", nullptr));
        checkBox_rts->setText(QApplication::translate("SerialPortTool", "RTS", nullptr));
        checkBox_dtr->setText(QApplication::translate("SerialPortTool", "DTR", nullptr));
        pushButton_manule_save->setText(QApplication::translate("SerialPortTool", "\346\211\213\345\212\250\344\277\235\345\255\230", nullptr));
        pushButton_open_log_doc->setText(QApplication::translate("SerialPortTool", "\346\211\223\345\274\200\346\227\245\345\277\227", nullptr));
        toolButton_highlight_key->setText(QApplication::translate("SerialPortTool", "\351\253\230\344\272\256", nullptr));
        checkBox_timer_send->setText(QApplication::translate("SerialPortTool", "\345\256\232\346\227\266\345\217\221\351\200\201", nullptr));
        lineEdit_timer_send_interval->setText(QApplication::translate("SerialPortTool", "1000", nullptr));
        label_7->setText(QApplication::translate("SerialPortTool", "ms/\346\254\241", nullptr));
        label_send_check->setText(QApplication::translate("SerialPortTool", "\345\217\221\351\200\201\346\240\241\351\252\214", nullptr));
        comboBox_send_check_func_list->setItemText(0, QApplication::translate("SerialPortTool", "\346\227\240\346\240\241\351\252\214", nullptr));
        comboBox_send_check_func_list->setItemText(1, QApplication::translate("SerialPortTool", "\346\240\241\351\252\214\345\222\214", nullptr));
        comboBox_send_check_func_list->setItemText(2, QApplication::translate("SerialPortTool", "CRC32", nullptr));
        comboBox_send_check_func_list->setItemText(3, QApplication::translate("SerialPortTool", "CRC16", nullptr));
        comboBox_send_check_func_list->setItemText(4, QApplication::translate("SerialPortTool", "ModbusCRC16", nullptr));

        label_9->setText(QApplication::translate("SerialPortTool", "\344\273\216\347\254\254", nullptr));
        lineEdit_start_bit->setText(QApplication::translate("SerialPortTool", "1", nullptr));
        label_10->setText(QApplication::translate("SerialPortTool", "\344\275\215\345\274\200\345\247\213", nullptr));
        label_11->setText(QApplication::translate("SerialPortTool", "\345\200\222\346\225\260\347\254\254", nullptr));
        lineEdit_end_bit->setText(QApplication::translate("SerialPortTool", "2", nullptr));
        label_12->setText(QApplication::translate("SerialPortTool", "\344\275\215\347\273\223\346\235\237", nullptr));
        comboBox_send_file->setItemText(0, QApplication::translate("SerialPortTool", "\350\257\267\351\200\211\346\213\251\350\246\201\344\274\240\351\200\201\347\232\204\346\226\207\344\273\266...", nullptr));
        comboBox_send_file->setItemText(1, QApplication::translate("SerialPortTool", "...", nullptr));

        comboBox_send_protocol->setItemText(0, QApplication::translate("SerialPortTool", "\350\257\267\351\200\211\346\213\251\344\274\240\350\276\223\345\215\217\350\256\256...", nullptr));
        comboBox_send_protocol->setItemText(1, QApplication::translate("SerialPortTool", "...", nullptr));

        pushButton_send_file->setText(QApplication::translate("SerialPortTool", "\345\274\200\345\247\213\344\274\240\351\200\201", nullptr));
        textEdit_send->setHtml(QApplication::translate("SerialPortTool", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\255\244\346\256\265\344\270\272\346\265\213\350\257\225\345\255\227\344\270\262:abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ</p></body></html>", nullptr));
        toolButton_data_curve->setText(QApplication::translate("SerialPortTool", "\346\233\262\347\272\277", nullptr));
        toolButton_set_curve->setText(QApplication::translate("SerialPortTool", "...", nullptr));
        toolButton_display_expand_cmd->setText(QApplication::translate("SerialPortTool", "\346\211\251\345\261\225", nullptr));
        checkBox_crlf->setText(QApplication::translate("SerialPortTool", "\345\233\236\350\275\246\346\215\242\350\241\214", nullptr));
        checkBox_timestamp->setText(QApplication::translate("SerialPortTool", "\346\227\266\351\227\264\346\210\263", nullptr));
        checkBox_hex_send->setText(QApplication::translate("SerialPortTool", "Hex\345\217\221\351\200\201", nullptr));
        checkBox_hex_recv->setText(QApplication::translate("SerialPortTool", "Hex\346\216\245\346\224\266", nullptr));
        pushButton_send_str->setText(QApplication::translate("SerialPortTool", "\345\217\221\351\200\201", nullptr));
        pushButton_clear_recv->setText(QApplication::translate("SerialPortTool", "\346\270\205\347\251\272\346\216\245\346\224\266", nullptr));
        checkBox_loop_send->setText(QApplication::translate("SerialPortTool", "\345\276\252\347\216\257\345\217\221\351\200\201", nullptr));
        pushButton_import_param->setText(QApplication::translate("SerialPortTool", "\345\257\274\345\205\245\345\217\202\346\225\260", nullptr));
        pushButton_save_param->setText(QApplication::translate("SerialPortTool", "\344\277\235\345\255\230\345\217\202\346\225\260", nullptr));
        pushButton_set_default->setText(QApplication::translate("SerialPortTool", "\346\201\242\345\244\215\351\273\230\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SerialPortTool: public Ui_SerialPortTool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALPORTTOOL_H
