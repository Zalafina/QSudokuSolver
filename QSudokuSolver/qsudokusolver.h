#ifndef QSUDOKUSOLVER_H
#define QSUDOKUSOLVER_H

#include <QWidget>
#include <QStylePainter>
#include <QStyleOptionFocusRect>
#include <QMessageBox>

#include "solver.h"
#include "sudokupuzzles.h"

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

    void PuzzlesInitCompleteProc(void);

private slots:
    void on_SolveButton_clicked();

    void on_ClearButton_clicked();

private:
    Ui::QSudokuSolver *ui;
    Solver m_Solver;
    bool m_SolvedStatus;

    SudokuPuzzles m_Puzzles;
};

#endif // QSUDOKUSOLVER_H
