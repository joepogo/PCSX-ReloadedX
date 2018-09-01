#ifndef H_CGUIMESSAGE
#define H_CGUIMESSAGE

#define GUI_MSG_CLICKED      01   // Control has been clicked
#define GUI_MSG_SETFOCUS     02  

class CGUIMessage
{
public:
	CGUIMessage(int iMsg, int iSenderID, int iControlID);
	~CGUIMessage();

	int GetMessage() const;
	int GetControlID() const;

private:
	int m_iMessage;
	int m_iSenderID;
	int m_iControlID;
};

#endif //H_CGUIMESSAGE