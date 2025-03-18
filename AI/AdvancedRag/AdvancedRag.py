
import os
import chromadb
from langchain_core.prompts import HumanMessagePromptTemplate, ChatPromptTemplate
from pypdf import PdfReader
from openai import OpenAI
from dotenv import load_dotenv
from langchain.text_splitter import RecursiveCharacterTextSplitter, SentenceTransformersTokenTextSplitter
from chromadb.utils.embedding_functions import SentenceTransformerEmbeddingFunction
from langchain_openai import OpenAIEmbeddings, ChatOpenAI
from langchain.prompts import PromptTemplate
from langchain.chains import LLMChain
from langchain.retrievers.multi_query import MultiQueryRetriever
from langchain.vectorstores import Chroma
from langchain_core.documents import Document

# class VDB:
#     def __init__(self):
#         self.chromaDB = chromadb.Client()
#         self.embeddingsFn = SentenceTransformerEmbeddingFunction()
#         self.collection = self.chromaDB.create_collection(
#             "microsoft-collection", embedding_function=self.embeddingsFn)
#         self.chromaDB

#     def addToDB(self, ids:list, docs:list):
#         self.collection.add(ids=ids, documents=docs)
#         return self.collection.count()

#     def query(self, qtext:str, topResults:int = 5):
#         result = self.collection.query(query_texts=[qtext], n_results=topResults)
#         retrieved_documents = result["documents"][0]
#         return retrieved_documents


def splitText(text:str):
    # https://dev.to/eteimz/understanding-langchains-recursivecharactertextsplitter-2846
    ch_splitter = RecursiveCharacterTextSplitter(chunk_size=1000, chunk_overlap=0)
    ch_split_text = ch_splitter.split_text("\n\n".join(pdf_text_list))
    tk_splitter = SentenceTransformersTokenTextSplitter(chunk_overlap=0, tokens_per_chunk=256)

    tk_split_text = []
    for text in ch_split_text:
        tk_split_text += tk_splitter.split_text(text)

    return tk_split_text


load_dotenv()
pdfReader = PdfReader("./NP.pdf")
pdf_text_list = [p.extract_text().strip() for p in pdfReader.pages]
pdf_text_list = [text for text in pdf_text_list if text]

sText = splitText(pdf_text_list)

ids = [str(i) for i in range(len(sText))]



# ================================================================================================
embed = OpenAIEmbeddings(
    model="text-embedding-ada-002", openai_api_key=os.environ.get("OPENAI_API_KEY"), disallowed_special=()
)

vecstore = Chroma(
    collection_name="NetworkProgramming",
    embedding_function=embed,
    persist_directory="./chroma_langchain_db",  # Where to save data locally, remove if not necessary
)

docs = []
for pair in zip(ids, sText):
    docs.append(Document(page_content=pair[1], metadata={"id": pair[0]}))
vecstore.add_documents(docs)

QA_PROMPT = PromptTemplate(
    input_variables=["query", "contexts"],
    template="""You are a helpful assistant who answers user queries using the
    contexts provided. If the question cannot be answered using the information
    provided say "I don't know".

    Contexts:
    {contexts}

    Question: {query}""",
)

gpt_llm = ChatOpenAI(openai_api_key="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", model_name="gpt-3.5-turbo")

chain = LLMChain(llm = gpt_llm, prompt = QA_PROMPT)

retriever = MultiQueryRetriever.from_llm(
    retriever=vecstore.as_retriever(), llm=gpt_llm
)

q = "What is the role of a socket in network programming?"
docs = retriever.get_relevant_documents(query=q)
response = chain(inputs={"query": q, "contexts": [doc.page_content for doc in docs]})
print(response["text"])

