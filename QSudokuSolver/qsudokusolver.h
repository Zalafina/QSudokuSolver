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

    void ChangeMode(const QString &ModeString);
public slots:
    void SolveSucceedProc(void);
    void InvalidSudokuPuzzleProc(void);

    void PuzzlesInitCompleteProc(void);

private slots:
    void on_SolveButton_clicked();

    void on_ClearButton_clicked();

    void on_ModeComboBox_currentIndexChanged(const QString &ComboBoxString);

    void on_PuzzleComboBox_currentIndexChanged(int index);

private:
    Ui::QSudokuSolver *ui;
    Solver m_Solver;
    bool m_SolvedStatus;

    SudokuPuzzles m_Puzzles;
};

#endif // QSUDOKUSOLVER_H
