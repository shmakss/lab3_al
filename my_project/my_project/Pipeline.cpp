#include "Pipeline.h"

Pipeline::Pipeline(CheckInput& check)
{
	this->check = &check;
}

void Pipeline::setPipeline(Pipe pipe) {
	pipeline.insert({ Pipe::getId(), pipe });
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
		pipe_id = check->checkInputInt("Какую трубу вы хотите редактировать?\n" + all_pipes, false);

	} while (!pipeline.count(pipe_id));
	pipeline.at(pipe_id).changeUnderRepair();
	std::cout << pipeline.at(pipe_id).showUnderRepair();
}
void Pipeline::changeUnderRepair(std::vector <int> ids) {
	if (ids.size() != 0) {
		for (int id : ids) {
			pipeline.at(id).changeUnderRepair();
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
	if (temp == "" or temp[0] != 's' or !check->isInputInt(temp.substr(1, temp.length() - 1), true)) {
		return false;
	}
	int amount = stoi(temp.substr(1, temp.length() - 1));
	for (int i = 0; i < amount; i++) {
		Pipe new_pipe(*check);
		if (new_pipe.write(in)) {
			temp_pipeline.insert({ Pipe::getId(),new_pipe });
		}
		else {
			return false;
		}
	}
	for (auto& [id, pipe] : temp_pipeline) {
		pipeline.insert({ id,pipe });
	}
	return true;
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
bool Pipeline::find(Pipe& pipe, std::string value) {
	return value == pipe.getName();
}
bool Pipeline::find(Pipe& pipe, bool value) {
	return pipe.getUnderRepair() == value;
}
bool Pipeline::editElement(int id) {
	if (pipeline.count(id)) {
		pipeline.at(id).changeUnderRepair();
		std::cout << "Готово!\n";
		return true;
	}
	else {
		return false;
	}
}
std::string Pipeline::showElement(int id) {
	if (pipeline.count(id)) {
		return "Элемент с идентификатором " + std::to_string(id) + "\n" + pipeline.at(id).showPipe();
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
	for (auto& [id, pipe] : pipeline) {
		if (!pipe.isInWork() and pipe.getDiameter() == diameter) {
			ids.push_back(id);
		}
	}
	return ids;
}
void Pipeline::getAJobForPipe(int id, int idInput, int idOutput)
{

	if (pipeline.count(id)) {
		pipeline.at(id).getAJob(idInput, idOutput);
	}

}
CheckInput& Pipeline::getCheckInput()
{
	return *check;
}
Pipe& Pipeline::findById(int id)
{

	if (pipeline.count(id)) {
		return pipeline.at(id);
	}

}
void Pipeline::clear() {
	pipeline.clear();
}
int Pipeline::size() {
	return pipeline.size();
}
std::ostream& operator << (std::ostream& os, Pipeline& pipeline) {
	return os << pipeline.showPipeline();
}
std::istream& operator >> (std::istream& in, Pipeline& pipeline) {
	Pipe newPipe(pipeline.getCheckInput());
	std::cin >> newPipe;
	pipeline.setPipeline(newPipe);
	return in;
}