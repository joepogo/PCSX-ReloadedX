#ifndef H_CGUIMESSAGE
#define H_CGUIMESSAGE

#define GUI_MSG_CLICKED		01   // Control has been clicked

class CGUIMessage
{
public:
	CGUIMessage(int iMsg, int iSenderID, int iControlID);
	~CGUIMessage();

	int GetMessage() const;
	int GetSenderID() const;

private:
	int m_iMessage;
	int m_iSenderID;
	int m_iControlID;
};

#endif //H_CGUIMESSAGE