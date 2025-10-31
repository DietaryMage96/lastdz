#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class AudioFile {
public:
    string name;
    double size;
    int duration;

    AudioFile(string n, double s, int d) : name(n), size(s), duration(d) {}
    virtual void play() = 0;
    virtual void info() {
        cout << "Name: " << name << ". Size: " << size << "MB. Duration: " << duration << " sec." << endl;
    }
    virtual string type() = 0;
    virtual ~AudioFile() {}
};

class MP3 : public AudioFile {
public:
    MP3(string n, double s, int d) : AudioFile(n, s, d) {}
    void play() override {
        cout << "MP3: Playback with loss - " << name << endl;
    }
    string type() {
        return "MP3";
    }
};

class WAV : public AudioFile {
public:
    WAV(string n, double s, int d) : AudioFile(n, s, d) {}
    void play() override {
        cout << "WAV: Playback without loss - " << name << endl;
    }
    string type() {
        return "WAV";
    }
};

class FLAC : public AudioFile {
public:
    FLAC(string n, double s, int d) : AudioFile(n, s, d) {}
    void play() override {
        cout << "FLAC: High-quality audio playback - " << name << endl;
    }
    string type() {
        return "FLAC";
    }
};

int main()
{
    vector<AudioFile*> playlist;

    ifstream file("playlist.txt");
    if (!file.is_open()) {
        cout << "Error" << endl;
    }

    string line;
    while (getline(file, line)) {
        string type, name, size, duration;
        string field;
        int count = 0;

        for (int i = 0; i < line.length(); i++) {
            if (line[i] == ';') {
                if (count == 0) type = field;
                else if (count == 1) name = field;
                else if (count == 2) size = field;
                field = "";
                count++;
            }
            else {
                field += line[i];
            }
        }
        duration = field;

        if (type == "MP3")
            playlist.push_back(new MP3(name, stod(size), stoi(duration)));
        else if (type == "WAV")
            playlist.push_back(new WAV(name, stod(size), stoi(duration)));
        else if (type == "FLAC")
            playlist.push_back(new FLAC(name, stod(size), stoi(duration)));
    }

    file.close();

    string a;
    cin >> a;
    while (a != "Exit" && a != "exit") {
        if (a == "Play" || a == "play") {
            for (int i = 0; i < playlist.size(); i++) {
                playlist[i]->play();
            }
            cin >> a;
        }
        else if (a == "Info" || a == "info") {
            for (int i = 0; i < playlist.size(); i++) {
                playlist[i]->info();
            }
            cin >> a;
        }
        else if (a == "Save" || a == "save") {
            ofstream file("playlist.txt");
            if (file.is_open()) {
                for (int i = 0; i < playlist.size(); i++) {
                    file << playlist[i]->type() << ";" << playlist[i]->name << ";" << playlist[i]->size << ";" << playlist[i]->duration << "\n";
                }
            }
            file.close();
            cout << "Playlist saved to file!" << endl;
            cin >> a;
        }
        else {
            cin >> a;
        }
    }
    for (int i = 0; i < playlist.size(); i++) {
        delete playlist[i];
    }
    playlist.clear();
}
