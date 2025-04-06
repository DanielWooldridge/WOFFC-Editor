#pragma once
#include "afxdialogex.h"
#include "resource.h"
#include <vector>
#include "SelectDialogue.h"
#include <algorithm>

class ToolMain;
class MFCMain;


class ObjectEditor : public CDialogEx
{
    DECLARE_DYNAMIC(ObjectEditor)

public:
    ObjectEditor(CWnd* pParent = nullptr);
    virtual ~ObjectEditor();
    void SetObjectData(std::vector<SceneObject>* SceneGraph, int* Selection);
    void SetToolMain(ToolMain* toolSystem) { m_toolSystem = toolSystem; }
    void OnEditControlChange();
    void End();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_OBJECTEDITOR_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    DECLARE_MESSAGE_MAP()
  

    std::vector<SceneObject>* m_sceneGraph;
    int* m_currentSelection;

private:
    CListBox m_ListBox;
    CEdit    m_NameEdit;
  
    ToolMain* m_toolSystem = nullptr; // Use pointer not full object

    CString m_PosXStr, m_PosYStr, m_PosZStr;
    CString m_RotXStr, m_RotYStr, m_RotZStr;
    CString m_ScaXStr, m_ScaYStr, m_ScaZStr;


public:
    afx_msg void OnLbnSelchangeList1();
    afx_msg void OnEnChangePosX();
    afx_msg void OnBnClickedArcball();
  
    afx_msg void OnBnClickedDuplicate();
    afx_msg void OnBnClickedDelete();
};

