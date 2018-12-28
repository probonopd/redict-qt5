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
    QTextEdit *m_orginEdit;
    QTextEdit *m_transEdit;
    QComboBox *m_typeBox;
    QPushButton *m_transBtn;
    YoudaoAPI *m_api;

    QMap<QString, QString> m_types;
};

#endif
