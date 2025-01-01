#include "Pipeline.h"



void Pipeline::setPipeline(Pipe pipe) {
	pipeline[Pipe::getId()] = pipe;
}
std::string Pipeline::showPipeline() {
	std::string output = "ТРУБОПРОВОД:\n";

	for (auto& [id, pipe] : pipeline) {
		output += "Элемент с идентификатором " + std::to_string(id) + "\n" + pipe.showPipe();

	}
	if (pipeline.size() == 0) {
		output += "-\n";
	}
	return output;
}
void Pipeline::changeUnderRepair(Input& input, std::ofstream error) {
	if (pipeline.size() == 0) {
		std::cout << "Для начала создайте трубы\n";
		return;
	}
	std::string all_pipes;
	for (auto& [id, pipe] : pipeline) {
		all_pipes += std::to_string(id) + ") " + pipe.getName() + " - " + pipe.showUnderRepair() + "\n";
	}
	int pipe_id;
	do {
		pipe_id = check.checkInputInt("Какую трубу вы хотите редактировать?\n" + all_pipes, false,input,error);

	} while (!pipeline.count(pipe_id));
	pipeline[pipe_id].changeUnderRepair();
	std::cout << pipeline[pipe_id].showUnderRepair();
}
void Pipeline::changeUnderRepair(std::vector <int> ids) {
	if (ids.size() != 0) {
		for (int id : ids) {
			pipeline[id].changeUnderRepair();
		}
	}
}
void Pipeline::save(std::ofstream& out) {
	out << "s" << pipeline.size() << "\n";
	if (pipeline.size() == 0) {
		out << "#\n";
		std::cout << "Вы не создали труб" << std::endl;
		return;
	}
	for (auto& [id, pipe] : pipeline) {
		pipe.save(out);
	}
	std::cout << "Трубы сохранены!" << std::endl;
	out << "#\n";
}
bool Pipeline::write(std::ifstream& in) {
	std::unordered_map<int, Pipe> temp_pipeline;
	std::string temp;
	std::getline(in, temp);
	if (temp == "" or temp[0] != 's' or !check.isInputInt(temp.substr(1, temp.length() - 1), true)) {
		return false;
	}
	int amount = stoi(temp.substr(1, temp.length() - 1));
	for (int i = 0; i < amount; i++) {
		Pipe new_pipe;
		if (new_pipe.write(in)) {
			temp_pipeline[Pipe::getId()] = new_pipe;
		}
		else {
			return false;
		}
	}
	for (auto& [id, pipe] : temp_pipeline) {
		pipeline[id] = pipe;
	}
	return true;
}
//К сожалению, вы получите копию элемента
Pipe Pipeline::getElement(int id) {
	if (pipeline.count(id)) {
		return pipeline[id];
	}
}
bool Pipeline::deleteElement(int id)
{
	if (pipeline.count(id)) {
		pipeline.erase(id);
		std::cout << "Готово!\n";
		return true;
	}
	else {
		return false;
	}

}
bool Pipeline::find(Pipe pipe, std::string value) {
	return value == pipe.getName();
}
bool Pipeline::find(Pipe pipe, bool value) {
	return pipe.getUnderRepair() == value;
}
bool Pipeline::editElement(int id, Input& input, std::ofstream& error) {
	if (pipeline.count(id)) {
		pipeline[id].changeUnderRepair();
		std::cout << "Готово!\n";
		return true;
	}
	else {
		return false;
	}
}
std::string Pipeline::showElement(int id) {
	if (pipeline.count(id)) {
		return "Элемент с идентификатором " + std::to_string(id) + "\n" + pipeline[id].showPipe();
	}
	else {
		return "";
	}
}
bool Pipeline::count(int id) {
	int count = 0;
	for (auto& element : pipeline) {
		if (element.first == id) {
			return true;
		}
	}
	return false;
}
std::vector<int> Pipeline::findDiameterForNetwork(int diameter)
{
	std::vector<int> ids;
	for (auto& [id,pipe] : pipeline) {
		if (!pipe.isInWork() and pipe.getDiameter() == diameter) {
			ids.push_back(id);
		}
	}
	return ids;
}
void Pipeline::getAJob(int id, int idInput, int idOutput)
{
	pipeline[id].getAJob(idInput,idOutput);
}
void Pipeline::clear() {
	pipeline.clear();
}
int Pipeline::size() {
	return pipeline.size();
}