#ifndef QSUDOKUSOLVER_H
#define QSUDOKUSOLVER_H

#include <QWidget>
#include <QStylePainter>
#include <QStyleOptionFocusRect>
#include <QMessageBox>

#include "Solver.h"

namespace Ui {
class QSudokuSolver;
}

class QSudokuSolver : public QWidget
{
    Q_OBJECT

public:
    explicit QSudokuSolver(QWidget *parent = 0);
    ~QSudokuSolver();

public slots:
    void SolveSucceedProc(void);
    void InvalidSudokuPuzzleProc(void);

private slots:
    void on_SolveButton_clicked();

    void on_ClearButton_clicked();

private:
    Ui::QSudokuSolver *ui;
    Solver m_Solver;
    bool m_SolvedStatus;
};

#endif // QSUDOKUSOLVER_H
