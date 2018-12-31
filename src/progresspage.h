#ifndef PROGRESSPAGE_H
#define PROGRESSPAGE_H

#include <QWidget>
#include <QStackedLayout>
#include "widgets/spinner.h"

class ProgressPage : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressPage(QWidget *parent = nullptr);

    void switchToProgress();
    void switchToError();
    void stop();

signals:
    void reloadButtonClicked();

private:
    QStackedLayout *stacked_layout_;
    Spinner *spinner_;
};

#endif // PROGRESSPAGE_H
