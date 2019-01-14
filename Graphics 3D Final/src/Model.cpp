#include "Model.h"

Model::Model(GLchar * Path)
{
	this->LoadModel(Path);
}

void Model::LoadModel(string path)
{
	cout << path << endl;
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}

	this->directory = path.substr(0, path.find_last_not_of('/'));

	this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode * node, const aiScene * scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->processMesh(mesh, scene));
	}

	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	vector<Vertex> Vertices;
	vector<GLuint> Indices;
	vector<Texture> Textures;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vectorPos;
		glm::vec3 vectorNormal;

		vectorPos.x = mesh->mVertices[i].x;
		vectorPos.y = mesh->mVertices[i].y;
		vectorPos.z = mesh->mVertices[i].z;
		vertex.Position = vectorPos;

		vectorNormal.x = mesh->mNormals[i].x;
		vectorNormal.y = mesh->mNormals[i].y;
		vectorNormal.z = mesh->mNormals[i].z;
		vertex.Normal = vectorNormal;

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 TextureVec;

			TextureVec.x = mesh->mTextureCoords[0][i].x;
			TextureVec.y = mesh->mTextureCoords[0][i].y;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		Vertices.push_back(vertex);


	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (GLuint j = 0; j < face.mNumIndices; j++)
		{
			Indices.push_back(face.mIndices[j]);
		}

	}

	/*if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* Material = scene->mMaterials[mesh->mMaterialIndex];


		vector<Texture> diffuseMaps = this->LoadMaterialTextures(Material, aiTextureType_DIFFUSE, "texture_diffuse");
		Textures.insert(Textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		vector<Texture> specualarMaps = this->LoadMaterialTextures(Material, aiTextureType_SPECULAR, "texture_specular");
		Textures.insert(Textures.end(), specualarMaps.begin(), specualarMaps.end());
	}*/
	return Mesh(Vertices,Indices,Textures);
}

vector<Texture> Model::LoadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName)
{
	vector<Texture> Textures;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString string;
		mat->GetTexture(type, i, &string);

		GLboolean skip = false;
		for (GLuint j = 0; j < Textures_Loaded.size(); j++)
		{
			if (std::strcmp(Textures_Loaded[j].Path.C_Str(), string.C_Str()) == 0);
			{
				Textures.push_back(Textures_Loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			Texture texture;
			texture.id = TextureFromFile(string.C_Str(), this->directory);
			texture.type = typeName;
			texture.Path = string;
			Textures.push_back(texture);
			this->Textures_Loaded.push_back(texture);
		}

	}
	return Textures;
}
void Model::Draw(GLuint ShaderProgram)
{
	for (GLuint i = 0; i < this->meshes.size(); i++)
	{
		this->meshes[i].Draw(ShaderProgram);
	}
}


GLint TextureFromFile(const char * path, string directory)
{
	string FileName = string(path);
	FileName = directory + '/' + FileName;
	GLuint TextureID;
	glGenTextures(1, &TextureID);
	const char* PATH = FileName.c_str();
	SDL_Surface* image = IMG_Load(PATH);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 100, 100, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SDL_FreeSurface(image);
	return TextureID;

	
}
