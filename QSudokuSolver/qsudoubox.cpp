#include <QDebug>
#include "qsudoubox.h"
#include "ui_qsudokusolver.h"

QSudouBox::QSudouBox(QWidget *parent) : QLabel(parent)
  , m_BoxType(BOXTYPE_BLANK)
  , parent_ptr(dynamic_cast<QSudokuSolver*>(parent))
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

void QSudouBox::setpuzzlenumber(void)
{
    this->setFrameShape(QFrame::WinPanel);
    this->setFrameShadow(QFrame::Sunken);
    this->setStyleSheet("background-color: orchid");
    this->m_BoxType = BOXTYPE_PUZZLE;
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

    if (QSudokuSolver::SUDOKUMODE_PLAY == parent_ptr->m_SudokuMode){
        if (true == this->text().isEmpty()){
            this->setFrameShape(QFrame::StyledPanel);
            this->setFrameShadow(QFrame::Plain);
            this->setStyleSheet("background-color:");

            this->m_BoxType = BOXTYPE_BLANK;
        }
        else{
            if (((0 == parent_ptr->GetUI()->PuzzleComboBox->currentIndex())
                 &&(true == parent_ptr->m_CustomPuzzleMaked))
                    ||(0 != parent_ptr->GetUI()->PuzzleComboBox->currentIndex())){
                this->setFrameShape(QFrame::StyledPanel);
                this->setFrameShadow(QFrame::Plain);
                this->setStyleSheet("background-color:");

                this->m_BoxType = BOXTYPE_FILL;
            }
            else{
                this->setStyleSheet("background-color: orchid");
                this->m_BoxType = BOXTYPE_PUZZLE;
            }
        }
    }
    else{ /* QSudokuSolver::SUDOKUMODE_SOLVE == QSudokuSolver::m_SudokuMode */
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
    case Qt::Key_Delete:
        this->clear();
    default:
        break;
    }

}
