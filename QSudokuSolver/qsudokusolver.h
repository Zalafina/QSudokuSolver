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

    enum SudokuPuzzleIndex
    {
        PUZZLE_CUSTOM = 0U,
    };
    Q_ENUM(SudokuPuzzleIndex)

    enum SudokuMode
    {
        SUDOKUMODE_PLAY = 0U,
        SUDOKUMODE_SOLVE,
    };
    Q_ENUM(SudokuMode)

    void ChangeMode(const QString &ModeString);
    Ui::QSudokuSolver *GetUI(void);
public slots:
    void SolveSucceedProc(void);
    void InvalidSudokuPuzzleProc(void);

    void PuzzlesInitCompleteProc(void);

private slots:
    void on_SolveButton_clicked();

    void on_ClearButton_clicked();

    void on_ModeComboBox_currentIndexChanged(const QString &ComboBoxString);

    void on_PuzzleComboBox_currentIndexChanged(int index);

    void on_CheckButton_clicked();

    void on_MakeButton_clicked();

private:
    void CheckButtonEnable(void);
    void CheckButtonDisable(void);
    void MakeButtonEnable(void);
    void MakeButtonDisable(void);
    void SolveButtonEnable(void);
    void SolveButtonDisable(void);

    bool CheckPuzzleInput(void);
    bool PlayModeSolveSucceed(void);
    void SolveModeSolveSucceed(void);

public:
    bool m_CustomPuzzleMaked;
    int m_SudokuMode;

private:
    Ui::QSudokuSolver *ui;
    Solver m_Solver;
    bool m_SolvedStatus;
    SudokuPuzzles m_Puzzles;
};

#endif // QSUDOKUSOLVER_H
