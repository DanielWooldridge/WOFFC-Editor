#include "ObjectEditor.h"
#include "ToolMain.h"


IMPLEMENT_DYNAMIC(ObjectEditor, CDialogEx)

BEGIN_MESSAGE_MAP(ObjectEditor, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &ObjectEditor::OnLbnSelchangeList1)
	ON_EN_CHANGE(IDC_POS_X, &ObjectEditor::OnEditControlChange)
	ON_EN_CHANGE(IDC_POS_Y, &ObjectEditor::OnEditControlChange)
	ON_EN_CHANGE(IDC_POS_Z, &ObjectEditor::OnEditControlChange)

	ON_EN_CHANGE(IDC_ROT_X, &ObjectEditor::OnEditControlChange)
	ON_EN_CHANGE(IDC_ROT_Y, &ObjectEditor::OnEditControlChange)
	ON_EN_CHANGE(IDC_ROT_Z, &ObjectEditor::OnEditControlChange)

	ON_EN_CHANGE(IDC_SCA_X, &ObjectEditor::OnEditControlChange)
	ON_EN_CHANGE(IDC_SCA_Y, &ObjectEditor::OnEditControlChange)
	ON_EN_CHANGE(IDC_SCA_Z, &ObjectEditor::OnEditControlChange)

	ON_BN_CLICKED(IDC_ARCBALL, &ObjectEditor::OnBnClickedArcball)
	ON_BN_CLICKED(IDC_DUPLICATE, &ObjectEditor::OnBnClickedDuplicate)
	ON_BN_CLICKED(IDC_DELETE, &ObjectEditor::OnBnClickedDelete)
END_MESSAGE_MAP()

ObjectEditor::ObjectEditor(CWnd* pParent)
    : CDialogEx(IDD_OBJECTEDITOR_DIALOG, pParent)
{
}

ObjectEditor::~ObjectEditor()
{
}

void ObjectEditor::SetObjectData(std::vector<SceneObject>* SceneGraph, int* Selection)
{
	m_sceneGraph = SceneGraph;
	m_currentSelection = Selection;

	// Clear existing items in the listbox
	m_ListBox.ResetContent();

	// Copy and sort the scene graph numerically by ID
	std::vector<SceneObject> sorted = *m_sceneGraph;
	std::sort(sorted.begin(), sorted.end(), [](const SceneObject& a, const SceneObject& b) {
		return a.ID < b.ID;
		});

	// Refill list box with sorted entries
	for (const auto& obj : sorted)
	{
		std::wstring entry = std::to_wstring(obj.ID);
		m_ListBox.AddString(entry.c_str());
	}

	// Ensure current selection is valid
	if (!m_sceneGraph->empty())
	{
		if (*m_currentSelection < 0 || *m_currentSelection >= m_sceneGraph->size())
		{
			*m_currentSelection = 0;
		}

		// Find the selected ID and match it in the sorted list
		int selectedID = m_sceneGraph->at(*m_currentSelection).ID;
		for (int i = 0; i < sorted.size(); ++i)
		{
			if (sorted[i].ID == selectedID)
			{
				m_ListBox.SetCurSel(i);
				break;
			}
		}
	}

	OnLbnSelchangeList1(); // Update fields
}


void ObjectEditor::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);


	DDX_Text(pDX, IDC_POS_X, m_PosXStr);
	DDX_Text(pDX, IDC_POS_Y, m_PosYStr);
	DDX_Text(pDX, IDC_POS_Z, m_PosZStr);

	DDX_Text(pDX, IDC_ROT_X, m_RotXStr);
	DDX_Text(pDX, IDC_ROT_Y, m_RotYStr);
	DDX_Text(pDX, IDC_ROT_Z, m_RotZStr);

	DDX_Text(pDX, IDC_SCA_X, m_ScaXStr);
	DDX_Text(pDX, IDC_SCA_Y, m_ScaYStr);
	DDX_Text(pDX, IDC_SCA_Z, m_ScaZStr);
}

void ObjectEditor::End()
{
    DestroyWindow(); 
}


void ObjectEditor::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here

	int selectionIndex = m_ListBox.GetCurSel(); // get index of selected item
	if (selectionIndex == LB_ERR || !m_sceneGraph) return;

	// Update the selection pointer
	*m_currentSelection = selectionIndex;

	// Get the object
	SceneObject& obj = m_sceneGraph->at(selectionIndex);

	// Fill position
	m_PosXStr.Format(L"%.2f", obj.posX);
	m_PosYStr.Format(L"%.2f", obj.posY);
	m_PosZStr.Format(L"%.2f", obj.posZ);

	// Fill rotation
	m_RotXStr.Format(L"%.2f", obj.rotX);
	m_RotYStr.Format(L"%.2f", obj.rotY);
	m_RotZStr.Format(L"%.2f", obj.rotZ);

	// Fill scale
	m_ScaXStr.Format(L"%.2f", obj.scaX);
	m_ScaYStr.Format(L"%.2f", obj.scaY);
	m_ScaZStr.Format(L"%.2f", obj.scaZ);

	// Push updates to the dialog
	UpdateData(FALSE);
}


void ObjectEditor::OnEditControlChange()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	if (!m_sceneGraph || !m_currentSelection || *m_currentSelection < 0 || *m_currentSelection >= m_sceneGraph->size())
		return;

	// Grab updated values from dialog box
	UpdateData(TRUE);

	SceneObject& obj = m_sceneGraph->at(*m_currentSelection);

	// Convert and apply position
	obj.posX = static_cast<float>(_tstof(m_PosXStr));
	obj.posY = static_cast<float>(_tstof(m_PosYStr));
	obj.posZ = static_cast<float>(_tstof(m_PosZStr));

	// Convert and apply rotation
	obj.rotX = static_cast<float>(_tstof(m_RotXStr));
	obj.rotY = static_cast<float>(_tstof(m_RotYStr));
	obj.rotZ = static_cast<float>(_tstof(m_RotZStr));

	// Convert and apply scale
	obj.scaX = static_cast<float>(_tstof(m_ScaXStr));
	obj.scaY = static_cast<float>(_tstof(m_ScaYStr));
	obj.scaZ = static_cast<float>(_tstof(m_ScaZStr));

	// Update the renderer
	m_toolSystem->UpdateObjectInDisplayList();


	//if (!m_sceneGraph || !m_currentSelection || *m_currentSelection < 0 || *m_currentSelection >= m_sceneGraph->size())
	//	return;

	//UpdateData(TRUE);

	//SceneObject& obj = m_sceneGraph->at(*m_currentSelection);

	//// Parse values from the text boxes
	//float inputX = static_cast<float>(_tstof(m_PosXStr));
	//float inputY = static_cast<float>(_tstof(m_PosYStr));
	//float inputZ = static_cast<float>(_tstof(m_PosZStr));

	//// Get camera vectors
	//DirectX::SimpleMath::Vector3 camForward = m_toolSystem->GetCamera()->GetForwardVector(); // Already normalized
	//DirectX::SimpleMath::Vector3 camRight = m_toolSystem->GetCamera()->GetRightVector();    // Already normalized
	//DirectX::SimpleMath::Vector3 worldUp(0.0f, 1.0f, 0.0f); // You can also get this from camera if needed

	//// Build new position based on camera-relative axes
	//DirectX::SimpleMath::Vector3 offset = (camRight * inputX) + (worldUp * inputY) + (camForward * inputZ);

	//// Update object position
	//obj.posX = offset.x;
	//obj.posY = offset.y;
	//obj.posZ = offset.z;

	//// Rotation
	//obj.rotX = static_cast<float>(_tstof(m_RotXStr));
	//obj.rotY = static_cast<float>(_tstof(m_RotYStr));
	//obj.rotZ = static_cast<float>(_tstof(m_RotZStr));

	//// Scale
	//obj.scaX = static_cast<float>(_tstof(m_ScaXStr));
	//obj.scaY = static_cast<float>(_tstof(m_ScaYStr));
	//obj.scaZ = static_cast<float>(_tstof(m_ScaZStr));

	//// Push changes to renderer
	//m_toolSystem->UpdateObjectInDisplayList();
	
	
}


void ObjectEditor::OnBnClickedArcball()
{
	//if (!m_sceneGraph || !m_currentSelection || *m_currentSelection < 0 || *m_currentSelection >= m_sceneGraph->size())
	//	return;

	//SceneObject& obj = m_sceneGraph->at(*m_currentSelection);
	//DirectX::SimpleMath::Vector3 target(obj.posX, obj.posY, obj.posZ);

	//m_toolSystem->StartArcballCamera(target);

	if (m_toolSystem)
	{
		m_toolSystem->ToggleArcball();
	}



}


void ObjectEditor::OnBnClickedDuplicate()
{
	if (!m_sceneGraph || !m_currentSelection || *m_currentSelection < 0 || *m_currentSelection >= m_sceneGraph->size())
		return;

	// Duplicate the original object
	SceneObject original = m_sceneGraph->at(*m_currentSelection);
	SceneObject copy = original;

	// Assign a new unique ID
	int maxID = 0;
	for (const auto& obj : *m_sceneGraph)
	{
		maxID = max(maxID, obj.ID);
	}
	copy.ID = maxID + 1;

	// Offset position slightly to make duplicate visible
	copy.posX += 1.0f;
	copy.posZ += 1.0f;

	// Add new object to scene
	m_sceneGraph->push_back(copy);

	// Update selection to new object
	*m_currentSelection = static_cast<int>(m_sceneGraph->size()) - 1;

	// Add entry to listbox
	std::wstring listEntry = std::to_wstring(copy.ID);
	m_ListBox.AddString(listEntry.c_str());
	m_ListBox.SetCurSel(*m_currentSelection);

	// Refresh property fields
	OnLbnSelchangeList1();

	// Tell renderer to refresh display list
	m_toolSystem->RebuildDisplayList();
}



void ObjectEditor::OnBnClickedDelete()
{
	// TODO: Add your control notification handler code here
	if (!m_sceneGraph || !m_currentSelection || *m_currentSelection < 0 || *m_currentSelection >= m_sceneGraph->size())
		return;

	// Remove object
	m_sceneGraph->erase(m_sceneGraph->begin() + *m_currentSelection);

	// Update selection
	if (*m_currentSelection >= m_sceneGraph->size())
		*m_currentSelection = static_cast<int>(m_sceneGraph->size()) - 1;

	// Clear and repopulate listbox
	m_ListBox.ResetContent();
	for (const auto& obj : *m_sceneGraph)
	{
		std::wstring entry = std::to_wstring(obj.ID);
		m_ListBox.AddString(entry.c_str());
	}

	if (*m_currentSelection >= 0)
	{
		m_ListBox.SetCurSel(*m_currentSelection);
		OnLbnSelchangeList1();
	}
	else
	{
		// Clear the fields
		m_PosXStr = m_PosYStr = m_PosZStr =
			m_RotXStr = m_RotYStr = m_RotZStr =
			m_ScaXStr = m_ScaYStr = m_ScaZStr = L"";
		UpdateData(FALSE);
	}

	// Rebuild the renderer list
	m_toolSystem->RebuildDisplayList(); // You should have a function for this
}
