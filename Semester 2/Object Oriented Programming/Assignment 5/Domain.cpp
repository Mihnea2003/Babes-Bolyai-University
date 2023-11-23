//
// Created by bro_b on 3/29/2023.
//
#include "Domain.h"
#include <vector>
#include <sstream>

Tutorial::Tutorial()
        : title{ "" }, presenter{ "" }, duration{ "" },likes{ 0 }, link{ "" }
{
}

Tutorial::Tutorial(const std::string& _title, const std::string& _presenter, const std::string& _duration, const int& _likes, const std::string& _link)
        : title{ _title }, presenter{ _presenter }, duration{ _duration}, likes{ _likes }, link{ _link }
{
}

Tutorial::Tutorial(const Tutorial& tutorial)
{
    this->title = tutorial.title;
    this->presenter = tutorial.presenter;
    this->duration = tutorial.duration;
    this->likes = tutorial.likes;
    this->link = tutorial.link;
}

std::string Tutorial::getTitle() const
{
    return this->title;
}

std::string Tutorial::getPresenter() const {
    return this->presenter;
}

std::string Tutorial::getDuration() const {
    return this->duration;
}

int Tutorial::getLike() const
{
    return this->likes;
}

std::string Tutorial::getLink() const
{
    return this->link;
}

void Tutorial::setTitle(std::string _title)
{
    this->title = _title;
}

void Tutorial::setPresenter(std::string _presenter)
{
    this->presenter = _presenter;
}

void Tutorial::setDuration(std::string _duration)
{
    this->duration = _duration;
}

void Tutorial::setLike(int _like)
{
    this->likes = _like;
}

void Tutorial::setLink(std::string _link)
{
    this->link = _link;
}

std::string Tutorial::toString() const
{
    auto likeStr = std::to_string(this->likes);
    return "Title: " + this->title + " | Presenter: " + this->presenter + " | Duration: " + this->duration +" | Likes: " + likeStr + " | Link: " + this->link;

}

Tutorial::~Tutorial() = default;

std::vector<std::string> tokenize(const std::string & str, char delimiter)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
    {
        result.push_back(token);
    }
    return result;
}

Tutorial& Tutorial::operator=(const Tutorial & tutorial)
{
    if (this == &tutorial)
    {
        return *this;
    }

    this->title = tutorial.title;
    this->presenter = tutorial.presenter;
    this->duration = tutorial.duration;
    this->likes = tutorial.likes;
    this->link = tutorial.link;

    return *this;
}

bool Tutorial::operator==(const Tutorial & checkTutorial) const
{
    return this->title == checkTutorial.title;
}

std::ostream& operator<<(std::ostream & os, const Tutorial & tutorial)
{
    os << tutorial.getTitle() << ",";
    os << tutorial.getPresenter() << ",";
    os << tutorial.getDuration() << ",";
    os << tutorial.getLike() << ",";
    os << tutorial.getLink();

    return os;
}

std::istream& operator>>(std::istream & reader, Tutorial & tutorial)
{
    std::string line;
    std::getline(reader, line);
    std::vector<std::string> tokens;
    tokens = tokenize(line, ',');
    tutorial.title = tokens[0];
    tutorial.presenter = tokens[1];
    tutorial.duration = tokens[2];
    tutorial.likes = std::stoi(tokens[3]);
    tutorial.link = tokens[4];
    return reader;
}
