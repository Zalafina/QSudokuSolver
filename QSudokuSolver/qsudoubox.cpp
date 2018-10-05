#include <QDebug>
#include "qsudoubox.h"

QSudouBox::QSudouBox(QWidget *parent) : QLabel(parent)
  , m_BoxType(BOXTYPE_BLANK)
{

}

void QSudouBox::clearall()
{
    this->clear();
    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Plain);
    this->setStyleSheet("background-color:");
    this->m_BoxType = BOXTYPE_BLANK;
}

void QSudouBox::focusInEvent(QFocusEvent *ev)
{
#ifdef DEBUG_LOGOUT_ON
    //qDebug() << "focusInEvent:" << this->objectName()<< ":" << "FocusReason:" << ev->reason();
#endif
    Q_UNUSED(ev);
    this->setFrameShape(QFrame::WinPanel);
    this->setFrameShadow(QFrame::Sunken);
    this->setStyleSheet("background-color: lightsteelblue");
}

void QSudouBox::focusOutEvent(QFocusEvent *ev)
{
#ifdef DEBUG_LOGOUT_ON
    //qDebug() << "focusOutEvent:" << this->objectName() << ":" << "FocusReason:" << ev->reason();
#endif
    Q_UNUSED(ev);
    if (true == this->text().isEmpty()){
        this->setFrameShape(QFrame::StyledPanel);
        this->setFrameShadow(QFrame::Plain);
        this->setStyleSheet("background-color:");
        this->m_BoxType = BOXTYPE_BLANK;
    }
    else{
        this->setStyleSheet("background-color: orchid");
        this->m_BoxType = BOXTYPE_PUZZLE;
    }
}

#if 0
void QSudouBox::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

//    QPainter painter(this);
//    QStyleOptionFocusRect option;
//    option.initFrom(this);
//    style()->drawPrimitive(QStyle::PE_FrameFocusRect, &option, &painter, this);

//    this->update();
}
#endif

void QSudouBox::keyPressEvent(QKeyEvent *keyevent)
{
    int keycode = keyevent->key();
    int keyvalue;
    QString str_key;

    switch (keycode)
    {
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
    case Qt::Key_7:
    case Qt::Key_8:
    case Qt::Key_9:
        keyvalue = keycode - Qt::Key_0;
        str_key.setNum(keyvalue);
        this->setText(str_key);
        break;
    case Qt::Key_0:
        this->clear();
    default:
        break;
    }

}
