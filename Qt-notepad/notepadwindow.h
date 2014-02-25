#ifndef NOTEPADWINDOW_H
#define NOTEPADWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QFontDialog>
#include <QClipboard>
#include <QKeySequence>
#include <QMessageBox>

#include <QToolBar>
#include <QIcon>

class NotepadWindow : public QMainWindow
{
    Q_OBJECT

public:
    NotepadWindow(QWidget *parent = 0);
    ~NotepadWindow();

private:
    QTextEdit* txtEditor_;
    QMenuBar* mainMenu_;
    QMenu* mnuArchivo_;
    QAction* actArchivoAbrir_;
    QAction* actArchivoGuardar_;
    QAction* actArchivoCerrar_;
    QMenu* mnuFormato_;
    QAction* actFormatoFuente_;
    QMenu* mnuEditar_;
    QAction* actEditarCopiar_;
    QAction* actEditarPegar_;
    QAction* actEditarCortar_;
    QAction* actEditarDeshacer_;
    QAction* actEditarRehacer_;
    // opcional 2
    QAction* actEditarBold_;
    QAction* actEditarItalic_;
    QAction* actEditarUnderline_;

    QClipboard * portapapeles_;
    QMenu* mnuAyuda_;
    QAction* actAyudaAcercade_;

public slots:
    void alAbrir();
    void alGuardar();
    void alFuente();
    void alAcercade();
    void alFuenteBold();
    void alFuenteItalic();
    void alFuenteUnderline();
};


#endif // NOTEPADWINDOW_H
