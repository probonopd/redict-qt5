#ifndef TRANSLATEPAGE_H
#define TRANSLATEPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include "youdaoapi.h"

class TranslatePage : public QWidget
{
    Q_OBJECT

public:
    TranslatePage(QWidget *parent = nullptr);
    ~TranslatePage();

protected:
    void keyPressEvent(QKeyEvent *);

private:
    void translate();
    void handleTranslateFinished(const QString &result);

private:
    QTextEdit *origin_edit_;
    QTextEdit *translate_edit_;
    QComboBox *type_combobox_;
    QPushButton *translate_btn_;
    YoudaoAPI *m_api;
};

#endif
