//=========================================================
//  LOS
//  Libre Octave Studio
//    $Id: lmaster.h,v 1.1.1.1.2.5 2005/12/11 21:29:23 spamatica Exp $
//  (C) Copyright 2000 Werner Schweer (ws@seh.de)
//=========================================================

#ifndef __LMASTER_EDIT_H__
#define __LMASTER_EDIT_H__

#include "AbstractMidiEditor.h"
#include "noteinfo.h"
#include "cobject.h"
#include "tempo.h"
///#include "sig.h"
//#include "al/sig.h"

#include <QTreeWidgetItem>

class QLineEdit;
class PosEdit;
class SigEdit;
class SigEvent;

enum LMASTER_LVTYPE
{
    LMASTER_TEMPO = 0,
    LMASTER_SIGEVENT
};

//---------------------------------------------------------
//   LMasterLViewItem
//!  QListViewItem base class for LMasterTempoItem and LMasterSigEventItem
//---------------------------------------------------------

class LMasterLViewItem : public QTreeWidgetItem
{
protected:
    QString c1, c2, c3, c4;

public:

    LMasterLViewItem(QTreeWidget* parent)
    : QTreeWidgetItem(QTreeWidgetItem::UserType)
    {
        parent->insertTopLevelItem(0, this);
    }
    virtual QString text(int column) const;
    virtual LMASTER_LVTYPE getType() = 0;
    virtual unsigned tick() = 0;
};

//---------------------------------------------------------
//   LMasterTempoItem
//!  QListViewItem which holds data for a TEvent
//---------------------------------------------------------

class LMasterTempoItem : public LMasterLViewItem
{
private:
    const TEvent* tempoEvent;

public:
    LMasterTempoItem(QTreeWidget* parent, const TEvent* t);

    virtual LMASTER_LVTYPE getType()
    {
        return LMASTER_TEMPO;
    }

    const TEvent* getEvent()
    {
        return tempoEvent;
    }

    virtual unsigned tick()
    {
        return tempoEvent->tick;
    }

    int tempo()
    {
        return tempoEvent->tempo;
    }
};

//---------------------------------------------------------
//   LMasterTempoItem
//!  QListViewItem which holds data for a SigEvent
//---------------------------------------------------------

class LMasterSigEventItem : public LMasterLViewItem
{
private:
    const SigEvent* sigEvent;

public:
    LMasterSigEventItem(QTreeWidget* parent, const SigEvent* s);

    virtual LMASTER_LVTYPE getType()
    {
        return LMASTER_SIGEVENT;
    }

    const SigEvent* getEvent()
    {
        return sigEvent;
    }

    virtual unsigned tick()
    {
        return sigEvent->tick;
    }

    int z()
    {
        return sigEvent->sig.z;
    }

    int n()
    {
        return sigEvent->sig.n;
    }
};


//---------------------------------------------------------
//   LMaster
//---------------------------------------------------------

class LMaster : public AbstractMidiEditor
{
    QTreeWidget* view;
    QToolBar* tools;
    QMenu* menuEdit;

    enum
    {
        CMD_DELETE, CMD_INSERT_SIG, CMD_INSERT_TEMPO, CMD_EDIT_BEAT, CMD_EDIT_VALUE
    };

    Q_OBJECT
    virtual void closeEvent(QCloseEvent*);
    void updateList();
    void insertTempo(const TEvent*);
    void insertSig(const SigEvent*);
    LMasterLViewItem* getItemAtPos(unsigned tick, LMASTER_LVTYPE t);
    void initShortcuts();
    QLineEdit* editor;
    PosEdit* pos_editor;
    // State-like members:
    LMasterLViewItem* editedItem;
    SigEdit* sig_editor;
    int editorColumn;
    bool editingNewItem;

    QAction *tempoAction, *signAction, *posAction, *_editEventValueAction, *delAction;

private slots:
    void select(QTreeWidgetItem*, QTreeWidgetItem*);
    void itemDoubleClicked(QTreeWidgetItem* item);
    void returnPressed();
    void itemPressed(QTreeWidgetItem* i, int column);
    void tempoButtonClicked();
    void timeSigButtonClicked();
    void cmd(int cmd);

public slots:
    void songChanged(int);
    void configChanged();

signals:
    void deleted(unsigned long);

public:
    LMaster();
    ~LMaster();
    virtual void readStatus(Xml&);
    virtual void writeStatus(int, Xml&) const;
    LMasterLViewItem* getLastOfType(LMASTER_LVTYPE t);


protected:
    virtual void keyPressEvent(QKeyEvent*);

};


#endif

