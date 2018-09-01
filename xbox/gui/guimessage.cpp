#include "guimessage.h"

CGUIMessage::CGUIMessage(int iMsg, int iSenderID, int iControlID)
{
	m_iMessage = iMsg;
	m_iSenderID = iSenderID;
	m_iControlID = iControlID;
}

CGUIMessage::~CGUIMessage()
{
}

int CGUIMessage::GetMessage() const
{
	return m_iMessage;
}

int CGUIMessage::GetControlID() const
{
	return m_iControlID;
}
