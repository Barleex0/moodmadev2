// moodmade.cpp 
#include <iostream>
#include <string>
#include <limits>

const int ARRAYSIZE = 20;


class MoodEntry
{
public:
	MoodEntry();
	MoodEntry(std::string date, int rating, std::string note);
	std::string getDate() const;
	int getRating() const;
	std::string getNote() const;
	void entry();
	void printEntry() const;
	void setDate(std::string datet ="unspecified");
	void setRating(int ratingt =3);
	void setNote(std::string notet= "no Note");
	bool set;// set bit flag for efficiency in reading
	std::string getMoodLabel() const;
private:
	int rating;
	std::string note, date;
};

std::string MoodEntry::getMoodLabel() const {
	switch (getRating())
	{
	case 1 :
		return "Very Bad";
	case 2:
		return "Bad";
	case 3:
		return "Okay";
	case 4:
		return "Good";
	case 5:
		return "Great";
	default:
		break;
	}
};

MoodEntry::MoodEntry()
{
	setDate();
	setNote();
	setRating();
	set = false;
};

MoodEntry::MoodEntry(std::string da, int rat, std::string no)
{
	setDate(da);
	setNote(no);
	setRating(rat);
	set = true;
};
void MoodEntry::setDate(std::string datet ) {
	date = datet;
};
void MoodEntry::setRating(int ratingt) {
	if (ratingt > -1 && ratingt < 6) {
		rating = ratingt;
	}
	else
	{
		rating = 3;
	};
};
void MoodEntry::setNote(std::string notet ) {
	note = notet;
}
std::string MoodEntry::getDate() const {
	return date;
};
std::string MoodEntry::getNote() const {
	return note;
};
int MoodEntry::getRating() const {
	return rating;
};
void MoodEntry::printEntry() const {
	std::cout << date << " rating :" << getMoodLabel() << " note " << note << '\n';
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
};

void MoodEntry::entry() {
	std::cout << "date :";
	std::string temp;
	std::cin >> temp;
	setDate(temp);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "rating :";
	int temp1;
	while (true) {
		std::cin >> temp1;
		//This forces an integer eventually
		if (std::cin.fail())
		{
			std::cout << "Error: Conversion to integer failed!\n enter a Number\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (temp1 < 1 || temp1 > 5) {

			std::cout << "Error: Number Out Of Range!\n 1 - 5 Are Valid Ratings\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		}

		else {
			
			break;
		};
	};

	setRating(temp1);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "note :";
	std::string temp2;
	getline(std::cin, temp2);
	setNote(temp2);
	
	set = true;
};

// watcher class
class MoodTracker
{
public:
	MoodTracker();
	
	void addEntry( MoodEntry& entry);

	void displayEntries() const;

	double calculateAverage() const;

	MoodEntry getHighestMood() const;

	MoodEntry getLowestMood() const;

	int getEntryCount() const;

private:
	MoodEntry entries[ARRAYSIZE];
	int entryCount;
};
MoodTracker::MoodTracker() {
	entryCount = 0;
};

void MoodTracker::addEntry( MoodEntry& entry) {
	entry.entry();
	entries[entryCount] = entry;
	entryCount++;
};


void MoodTracker::displayEntries() const {
	for (MoodEntry var : entries)
	{
		if (var.set) {
			var.printEntry();

		}
		else
		{
			break;
		}
	};
};

double MoodTracker::calculateAverage() const {
	int acc = 0;
	for (int v = 0;v < ARRAYSIZE;v++)
	{
		if (entries[v].set) {
			acc += entries[v].getRating();


		}
		else
		{
			if (v != 0) {
				return acc / v;
			}
			return 0;
		}

	};
};

MoodEntry MoodTracker::getHighestMood() const {
	int acc = 0;
	int high = 0;
	for (int v = 0;v < ARRAYSIZE;v++)
	{
		if (entries[v].set) {
			if (entries[v].getRating() > high) {
				high = entries[v].getRating();
				acc = v;
			};


		}
		else
		{
			return entries[acc];

		};

	};
};

MoodEntry MoodTracker::getLowestMood() const {
	int acc = 0;
	int high = 90;
	for (int v = 0;v < ARRAYSIZE;v++)
	{
		if (entries[v].set) {
			if (entries[v].getRating() < high) {
				high = entries[v].getRating();
				acc = v;
			};


		}
		else
		{
			return entries[acc];

		};

	};
}

int MoodTracker::getEntryCount() const {
	return entryCount;
};



char menu[] = "\n 1 Add entry, 2 View entries, 3 View average rating, 4 Get Highest mood, 5 Get Lowest Mood, 6 Exit.\n";




int cursor = 0;
MoodEntry moods[ARRAYSIZE];
MoodTracker moTr;

// process loop
void loop(){
	std::cout << menu;
	int value; 
	std::cin >> value;
	MoodEntry x;
	switch (value)
	{
	case 1:
		moTr.addEntry(x);
		break;

	case 2:
		moTr.displayEntries();
		break;
	case 3:
		std::cout << moTr.calculateAverage();
		break;
	case 4:
		moTr.getHighestMood().printEntry();
		break;
	case 5:
		moTr.getLowestMood().printEntry();
		break;
	default:
		exit(EXIT_SUCCESS);
	};



}


int main()

{
	while (true)
	{
		loop();
	}
	


}

