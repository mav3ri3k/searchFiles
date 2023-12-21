from sentence_transformers import SentenceTransformer
from langchain.text_splitter import CharacterTextSplitter
from PyPDF2 import PdfReader
from qdrant_client import models, QdrantClient
import info_retrieval as llm

pdf = "dm theorems.pdf"

pdf_reader = PdfReader(pdf)
text = ""

print("Pdf openned")

for page in pdf_reader.pages:
    text += page.extract_text()

text_splitter = CharacterTextSplitter(
        separator="\n",
        chunk_size = 1000,
        chunk_overlap = 200,
        length_function = len)
chunks = text_splitter.split_text(text)

print("Chunks created")

documents = []
for id, chunk in enumerate(chunks):
    documents.append(
        {
            "doc_name":f"{pdf}",
            "id":id,
            "chunk":f"{chunk}"
        }
    )

encoder = SentenceTransformer("TaylorAI/bge-micro-v2")

print("Encoder obtained")

embeddings = encoder.encode(chunks)

# local computer will use its memory as temporary storage.
qdrant = QdrantClient(":memory:")


qdrant.recreate_collection(
    collection_name="pdf",
    vectors_config=models.VectorParams(
        size=encoder.get_sentence_embedding_dimension(),  # Vector size is defined by used model
        distance=models.Distance.COSINE,
    ),
)

print("Database created")

qdrant.upload_records(
    collection_name="pdf",
    records=[
        models.Record(
            id=idx, vector=encoder.encode(doc["chunk"]).tolist(), payload=doc
        )
        for idx, doc in enumerate(documents)
    ],
)

print("Embedding for chunks stored")

question = input("Ask a question: ")

hits = qdrant.search(
    collection_name="pdf",
    query_vector=encoder.encode(question).tolist(),
    limit=3,
)

for hit in hits:
    print(hit.payload, "score:", hit.score)
    
# Sample Test Instruction Used by Youtuber Sam Witteveen https://www.youtube.com/@samwitteveenai
system = f'You are an AI assistant which is used for information from given text. Your should be very carefull in answering the user instructions based on the following chunk of text and do not hallisunate. Chunk of text: {hits[0]}'
instruction = question
print(llm.generate_text(system, instruction))