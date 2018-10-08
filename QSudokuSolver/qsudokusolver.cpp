#include <QDebug>
#include "qsudokusolver.h"
#include "ui_qsudokusolver.h"

QSudokuSolver::QSudokuSolver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QSudokuSolver),
    m_Solver(this),
    m_SolvedStatus(false),
    m_Puzzles(this)
{
    ui->setupUi(this);

    ui->SolveButton->setStyleSheet("color: royalblue");
    ui->ClearButton->setStyleSheet("color: red");
    ui->CheckButton->setStyleSheet("color: forestgreen");
    ui->MakeButton->setStyleSheet("color: orchid");

    ChangeMode(QString("Play Sudoku"));

    QObject::connect(&m_Solver, &Solver::SolveSucceed, this, &QSudokuSolver::SolveSucceedProc);
    QObject::connect(&m_Solver, &Solver::InvalidSudokuPuzzle, this, &QSudokuSolver::InvalidSudokuPuzzleProc);

    QObject::connect(&m_Puzzles, &SudokuPuzzles::initComplete, this, &QSudokuSolver::PuzzlesInitCompleteProc);
}

QSudokuSolver::~QSudokuSolver()
{
    delete ui;
}

void QSudokuSolver::ChangeMode(const QString &ModeString)
{
    if (ModeString == QString("Play Sudoku")){
        ui->SolveButton->setVisible(false);
        ui->ClearButton->setVisible(false);

        ui->CheckButton->setVisible(true);
        ui->MakeButton->setVisible(true);
        ui->CheckButton->setText("Check");
        ui->MakeButton->setText("Make");

        if (0 == ui->PuzzleComboBox->currentIndex()){
            on_PuzzleComboBox_currentIndexChanged(0);
        }
        else{
            ui->PuzzleComboBox->setCurrentIndex(0);
        }
    }
    else if (ModeString == QString("Solve Sudoku")){
        ui->CheckButton->setVisible(false);
        ui->MakeButton->setVisible(false);

        ui->SolveButton->setVisible(true);
        ui->ClearButton->setVisible(true);
        ui->SolveButton->setText("Solve");
        ui->ClearButton->setText("Clear");

        if (0 == ui->PuzzleComboBox->currentIndex()){
            on_PuzzleComboBox_currentIndexChanged(0);
        }
        else{
            ui->PuzzleComboBox->setCurrentIndex(0);
        }
    }
}

void QSudokuSolver::SolveSucceedProc(void)
{
    int row, col, valbit, val, Square = 0;
    char ch;

    int EntryBuffer[81];
    m_Solver.GetEntryResult(EntryBuffer);

    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            QString str_row, str_col, box_name;
            str_row.setNum(row+1);
            str_row.prepend(QChar('R'));
            str_col.setNum(col+1);
            str_col.prepend(QChar('C'));
            box_name = QString("Box") + str_row + str_col;

            valbit = EntryBuffer[Square++];
            if (valbit != 0){
                for (val = 1; val <= 9; val++){
                    if (valbit == (1 << val)) {
                        ch = '0' + val;
                        break;
                    }
                }

                //set ch to Box Text
                QSudouBox *box = this->findChild<QSudouBox *>(box_name);
                if (box != nullptr){
                    if((QSudouBox::BOXTYPE_BLANK == box->m_BoxType)
                            && (true == box->text().isEmpty())){
                        box->setText(QString(ch));
                    }
                }
                else{
                    qDebug() << "SolveSucceedProc Find BoxName Error:" << box_name;
                }
            }
            else {
            }
        }
    }


    ui->SolveButton->setEnabled(false);
    ui->SolveButton->setText("Solved");
    ui->SolveButton->setStyleSheet("color: darkgray");

    for (const QString &boxname : m_Solver.m_BoxMap)
    {
        QSudouBox *box = this->findChild<QSudouBox *>(boxname);
        if (box != nullptr){
            box->setEnabled(false);
        }
        else{
            qDebug() << "ClearButton Find BoxName Error:" << boxname;
        }
    }

    m_SolvedStatus = true;
}

void QSudokuSolver::InvalidSudokuPuzzleProc(void)
{
    m_SolvedStatus = false;
    QMessageBox::warning(this, tr("QKeyMapper"), tr("<html><head/><body><p align=\"center\">Input invalid Sudoku Puzzle.</p><p align=\"center\">Reinput it please!</p></body></html>"));
}

void QSudokuSolver::PuzzlesInitCompleteProc(void)
{
    int puzzletablesize = m_Puzzles.m_SudokuPuzzleList.size();

    for (int loop = 1; loop <= puzzletablesize; loop++){
        QString puzzle_number;
        puzzle_number = QString("%1").arg(loop, 3, 10, QChar('0'));
        QString combobox_String = QString("Puzzle ") + puzzle_number;
        ui->PuzzleComboBox->addItem(combobox_String);
    }
}

void QSudokuSolver::on_SolveButton_clicked()
{
    //QSudouBox *box = this->findChild<QSudouBox *>("BoxR1C5");
    //box->setText("5");
    char matrix[9][9];
    memset(matrix, '-', sizeof(matrix));
    for (const QString &boxname : m_Solver.m_BoxMap)
    {
        QSudouBox *box = this->findChild<QSudouBox *>(boxname);
        if (box != nullptr){
            quint32 index = m_Solver.m_BoxMap.key(boxname);
            int row = Solver::index2row(index);
            int col = Solver::index2col(index);

            QString boxtext = box->text();
            bool isNumber = false;
            int value = boxtext.toInt(&isNumber);
            if ((false == boxtext.isEmpty())
                    && (QSudouBox::BOXTYPE_PUZZLE == box->m_BoxType)
                    && (true == isNumber)
                    && (1<= value && value <= 9)){
                matrix[row-1][col-1] = boxtext.toStdString().c_str()[0];
            }

#ifdef DEBUG_LOGOUT_ON
            //qDebug("index(%d), row(%d), col(%d), name(%s)", index, Solver::index2row(index), Solver::index2col(index), boxname.toStdString().c_str());
#endif
        }
        else{
            qDebug() << "SolveButton Find BoxName Error:" << boxname;
        }
    }

    m_Solver.SudokuSolve(matrix);
}

void QSudokuSolver::on_ClearButton_clicked()
{
    for (const QString &boxname : m_Solver.m_BoxMap)
    {
        QSudouBox *box = this->findChild<QSudouBox *>(boxname);
        if (box != nullptr){
            box->setEnabled(true);
            box->clearall();
        }
        else{
            qDebug() << "ClearButton Find BoxName Error:" << boxname;
        }
    }

    m_SolvedStatus = false;
    m_Solver.ClearSolvedStatus();
    ui->SolveButton->setStyleSheet("color: royalblue");
    ui->SolveButton->setText("Solve");
    ui->SolveButton->setEnabled(true);
}

void QSudokuSolver::on_ModeComboBox_currentIndexChanged(const QString &ComboBoxString)
{
    if (ComboBoxString == QString("Play Sudoku")){
#ifdef DEBUG_LOGOUT_ON
        qDebug() << "Mode Changed:" << ComboBoxString;
#endif

        ChangeMode(ComboBoxString);
    }
    else if (ComboBoxString == QString("Solve Sudoku")){
#ifdef DEBUG_LOGOUT_ON
        qDebug() << "Mode Changed:" << ComboBoxString;
#endif

        ChangeMode(ComboBoxString);
    }
}

void QSudokuSolver::on_PuzzleComboBox_currentIndexChanged(int index)
{
#ifdef DEBUG_LOGOUT_ON
    qDebug() << "PuzzleComboBox IndexChanged:" << index;
#endif

    if (0 == index){
        for (const QString &boxname : m_Solver.m_BoxMap)
        {
            QSudouBox *box = this->findChild<QSudouBox *>(boxname);
            if (box != nullptr){
                box->setEnabled(true);
                box->setFocusPolicy(Qt::ClickFocus);
                box->clearall();
            }
            else{
                qDebug() << "ChangeMode Find BoxName Error:" << boxname;
            }
        }

        m_SolvedStatus = false;
        m_Solver.ClearSolvedStatus();
        ui->SolveButton->setStyleSheet("color: royalblue");
        ui->SolveButton->setEnabled(true);
    }
    else if (index < m_Puzzles.m_SudokuPuzzleList.size()){
#ifdef DEBUG_LOGOUT_ON
        qDebug() << "Sudoku:" << m_Puzzles.m_SudokuPuzzleList.at(index-1);
#endif


    }
    else{
        qDebug() << "PuzzleComboBox IndexError:" << index;
    }
}
