from google.cloud import firestore
from google.auth import compute_engine
from langchain_google_firestore import FirestoreChatMessageHistory
from langchain_openai import ChatOpenAI
from langchain_core.messages import AIMessage, HumanMessage, SystemMessage 


PROJECT_ID = "chathistory-90b14"
SESSION_ID = "chat-history-session"
COLLECTION_NAME = "chat_history"

fireStoreClient = firestore.Client(project=PROJECT_ID)
chat_history = FirestoreChatMessageHistory(session_id=SESSION_ID,
                                            collection=COLLECTION_NAME,
                                            client=fireStoreClient)
print("Current chat history:", chat_history.messages)

model = ChatOpenAI(model="gpt-4o", temperature=0.3)

list_of_message = [
    SystemMessage(content="You are a match teacher, help me to resolve the following math problems"),
    HumanMessage(content="2 + 2 is = with ?")
]

while(True):
    currentMessage = input("You: ")
    if(currentMessage == "exit"):
        break

    chat_history.add_user_message(currentMessage)
    ai_response = model.invoke(chat_history.messages)
    chat_history.add_ai_message(ai_response.content)
    print("AI: ", ai_response.content)



