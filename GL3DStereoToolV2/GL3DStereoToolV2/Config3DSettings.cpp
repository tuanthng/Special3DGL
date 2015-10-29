#include "Config3DSettings.h"


Config3DSettings::Config3DSettings()
{
	currentDrawingBuffer = GL_BACK;
	currentFrameGL = 0;
	currentBoundaryLoc = ObjectBoundary::Start;
	currentObjectType = ObjectType::Background;
}


Config3DSettings::~Config3DSettings()
{

}
bool Config3DSettings::readConfig3DSettingsFromFile(const std::string & fileName)
{
	// open the file
	ifstream input(fileName.c_str());
	if (!input) return false;

	struct {
		// convert string to boolean
		bool readBool(std::string text) {
			// convert to lower case
			std::transform(text.begin(), text.end(), text.begin(), ::tolower);

			// accept sensible values for true (anything else is false)
			return (text == "yes") || (text == "true") || (text == "1");
		}
	} local;

	// read key
	string key;

	do {
		string line;
		//input >> ws >> line;
		input >> line;

		if (!input) break;

		// identify the key
		if (line == "#DrawingBuffer:")
		{
			key = "#DrawingBuffer:";
			line = "";
		}
		else if (line == "#Frame:")
		{
			key = "#Frame:";
			line = "";
		}
		else if (line == "#Background:")
		{
			key = "#Background:";
			line = "";
		}
		else if (line == "#Foregound:")
		{
			key = "#Foregound:";
			line = "";
		}
		else {
			// unrecognised keys are currently ignored
		}

		// look for values for the current key
		if (key == "#DrawingBuffer:" && line.length() > 0)
		{
			std::cout << "DrawingBuffer: " << endl;

			//for each value, parse it into 3 parts: key, value and comment (if has). The comment is specified by the ; and key by the :
			if (line.length() > 0)
			{
				size_t pos = 0;
				std::string token;
				pos = line.find(";"); //find comments

				std::cout << "Line: " << line << endl;
				std::cout << "Pos 1: " << pos << endl;
				if (pos != std::string::npos)
				{
					line.erase(pos, line.length() - pos);
				}
				
				pos = line.find(":");

				if (pos != std::string::npos)
				{
					string subKey = line.substr(0, pos);
					string value = line.substr(pos + 1, line.length() - pos - 1);
					
					std::cout << "subKey: " << subKey << endl;
					std::cout << "value: " << value << endl;
					
					if (subKey == "Buffer")
					{
						this->BufferIndex = convertStringToInt(value);
					}
				}
			}
		}
		else if (key == "#Frame:" && line.length() > 0)
		{
			std::cout << "Frame: " << endl;

			//for each value, parse it into 3 parts: key, value and comment (if has). The comment is specified by the ; and key by the :
			if (line.length() > 0)
			{
				size_t pos = 0;
				std::string token;
				pos = line.find(";"); //find comments

				std::cout << "Line: " << line << endl;
				std::cout << "Pos 1: " << pos << endl;
				if (pos != std::string::npos)
				{
					line.erase(pos, line.length() - pos);
				}

				pos = line.find(":");

				if (pos != std::string::npos)
				{
					string subKey = line.substr(0, pos);
					string value = line.substr(pos + 1, line.length() - pos - 1);

					std::cout << "subKey: " << subKey << endl;
					std::cout << "value: " << value << endl;

					if (subKey == "StartFrame")
					{
						this->StartInterceptedFrame = convertStringToLong(value);
					}
				}
			}
		}
		else if (key == "#Background:" && line.length() > 0)
		{
			std::cout << "Background: " << endl;

			if (line.length() > 0)
			{
				size_t pos = 0;
				std::string token;
				pos = line.find(";"); //find comments

				std::cout << "Line: " << line << endl;

				if (pos != std::string::npos)
				{
					line.erase(pos, line.length() - pos);
				}

				pos = line.find(":");

				if (pos != std::string::npos)
				{
					string subKey = line.substr(0, pos);
					string value = line.substr(pos + 1, line.length() - pos - 1);

					std::cout << "subKey: " << subKey << endl;
					std::cout << "value: " << value << endl;

					if (subKey == "StartFunctionCallBackground")
					{
						this->StartFunctionCallBackground = value;
					}
					else if (subKey == "StartFunctionCallBackgroundNumber")
					{
						this->StartFunctionCallBackgroundNumber = convertStringToLong(value);
					}
					else if (subKey == "EndFunctionCallBackground")
					{
						this->EndFunctionCallBackground = value;
					}
					else if (subKey == "EndFunctionCallBackgroundNumber")
					{
						this->EndFunctionCallBackgroundNumber = convertStringToLong(value);
					}
				}
			}
		}
		else if (key == "#Foregound:" && line.length() > 0)
		{
			std::cout << "Foregound: " << endl;

			if (line.length() > 0)
			{
				size_t pos = 0;
				std::string token;
				pos = line.find(";"); //find comments

				std::cout << "Line: " << line << endl;

				if (pos != std::string::npos)
				{
					line.erase(pos, line.length() - pos);
				}

				pos = line.find(":");

				if (pos != std::string::npos)
				{
					string subKey = line.substr(0, pos);
					string value = line.substr(pos + 1, line.length() - pos - 1);

					std::cout << "subKey: " << subKey << endl;
					std::cout << "value: " << value << endl;

					if (subKey == "StartFunctionCallForegound")
					{
						this->StartFunctionCallForegound = value;
					}
					else if (subKey == "StartFunctionCallForegoundNumber")
					{
						this->StartFunctionCallForegoundNumber = convertStringToLong(value);
					}
					else if (subKey == "EndFunctionCallForegound")
					{
						this->EndFunctionCallForegound = value;
					}
					else if (subKey == "EndFunctionCallForegoundNumber")
					{
						this->EndFunctionCallForegoundNumber = convertStringToLong(value);
					}
				}
			}
		}

	} while (true);

	// close the file
	input.close();

	return true;
}
int Config3DSettings::convertStringToInt(string s)
{
	int number;
	istringstream buffer(s);
	buffer >> number;

	return number;
}
long Config3DSettings::convertStringToLong(string s)
{
	long number;
	istringstream buffer(s);
	buffer >> number;

	return number;
}
bool Config3DSettings::checkFunctionCall(const string funcName, ObjectType objType, ObjectBoundary bound)
{
	switch (objType)
	{
	case Background:
		switch (bound)
		{
		case Start:
			if (funcName.compare(StartFunctionCallBackground) == 0)
			{
				return true;
			}
			
			break;
		case End:
			if (funcName.compare(EndFunctionCallBackground) == 0)
			{
				return true;
			}
			break;
		default:
			break;
		}
		break;
	case Foreground:
		switch (bound)
		{
		case Start:
			if (funcName.compare(StartFunctionCallForegound) == 0)
			{
				return true;
			}
			break;
		case End:
			if (funcName.compare(EndFunctionCallForegound) == 0)
			{
				return true;
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	
	return false;
}
bool Config3DSettings::checkFunctionCallNumber(long indexCall, ObjectType objType, ObjectBoundary bound)
{
	switch (objType)
	{
	case Background:
		switch (bound)
		{
		case Start:
			return indexCall == StartFunctionCallBackgroundNumber;
			break;
		case End:
			return indexCall == EndFunctionCallBackgroundNumber;
			break;
		default:
			break;
		}
		break;
	case Foreground:
		switch (bound)
		{
		case Start:
			return indexCall == StartFunctionCallForegoundNumber;
			break;
		case End:
			return indexCall == EndFunctionCallForegoundNumber;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return false;
}
void Config3DSettings::getDrawingBuffer(const string funcName, GLuint &buffer, ObjectType &objType, ObjectBoundary &bound, bool updated)
{
	buffer = GL_BACK;
	objType = ObjectType::Background;
	bound = ObjectBoundary::Middle;

	/*buffer = this->currentDrawingBuffer;
	objType = this->currentObjectType;
	bound = this->currentBoundaryLoc;*/

	if (funcName.compare(StartFunctionCallForegound) == 0 && (currentFunctionCallIndexPerFrame == StartFunctionCallForegoundNumber))
	{
		buffer = getBuffer();
		objType = ObjectType::Foreground;
		bound = ObjectBoundary::Start;

		std::cout << "In forground start: " << funcName << endl;
		std::cout << "Index start: " << currentFunctionCallIndexPerFrame << endl;
		std::cout << "Buffer Index : " << this->BufferIndex << endl;
	}
	else if (funcName.compare(EndFunctionCallForegound) == 0 && (currentFunctionCallIndexPerFrame == EndFunctionCallForegoundNumber))
	{
		buffer = getBuffer();
		objType = ObjectType::Foreground;
		bound = ObjectBoundary::Start;
		std::cout << "In forground end: " << funcName << endl;
		std::cout << "Index end: " << currentFunctionCallIndexPerFrame << endl;
		std::cout << "Buffer Index : " << this->BufferIndex << endl;
	}
	/*else if (funcName.compare(StartFunctionCallBackground) == 0 && (currentFunctionCallIndexPerFrame == StartFunctionCallBackgroundNumber))
	{
		buffer = GL_BACK;
		objType = ObjectType::Background;
		bound = ObjectBoundary::Start;
	}
	else if (funcName.compare(EndFunctionCallBackground) == 0 && (currentFunctionCallIndexPerFrame == EndFunctionCallBackgroundNumber))
	{
		buffer = GL_BACK;
		objType = ObjectType::Background;
		bound = ObjectBoundary::End;
	}*/

	if (updated)
	{
		//only update if the current drawing buffer is not BACK and in the middle of the drawing of the foreground
		if (!(currentDrawingBuffer != GL_BACK && currentBoundaryLoc == ObjectBoundary::Middle))
		{
			currentDrawingBuffer = buffer;
			currentBoundaryLoc = bound;
			currentObjectType = objType;
		}
		
	}
}
void Config3DSettings::getDrawingBuffer(const string funcName)
{
	GLuint buffer; 
	ObjectType objType;
	ObjectBoundary bound;
	bool updated = true;

	getDrawingBuffer(funcName, buffer, objType, bound, updated);

}
void Config3DSettings::resetCurrentStatusOfEachFrame()
{
	currentDrawingBuffer = GL_BACK;
	currentBoundaryLoc = ObjectBoundary::Start;
	currentObjectType = ObjectType::Background;
}
