/*
 * Project : Pulsar 2018 - Image Processing
 */

#ifndef SCRIPTBOX_H
#define SCRIPTBOX_H

#include <QDialog>
#include <QGridLayout>
#include <QTextEdit>
#include <QPushButton>

class ScriptBox : public QDialog
{
    Q_OBJECT

public:
    explicit ScriptBox(QWidget *parent);

public slots:
    void apply(void);
    void run(void);

signals:
    void sApply(const QString& sources);

private:
    QGridLayout     *mLayout;
    QTextEdit       *mTextEdit;
    QPushButton     *mCancelButton;
    QPushButton     *mApplyButton;
};

#endif // SCRIPTBOX_H
