//
// Created by bro_b on 3/29/2023.
//

#ifndef OOP_LAB4_DOMAIN_H
#define OOP_LAB4_DOMAIN_H
#pragma once

#include <string>
#include <iostream>

class Tutorial {
private:
    std::string title;
    std::string presenter;
    std::string duration;
    int likes;
    std::string link;

public:
    /// <summary>
    /// Constructor for the tutorial
    /// </summary>
    Tutorial();

    /// <summary>
    /// Constructor for the tutorial
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    /// <param name=""></param>
    /// <param name=""></param>
    Tutorial(const std::string&, const std::string&, const std::string&, const int&, const std::string&);

    /// <summary>
    /// Constructor for the tutorial
    /// </summary>
    /// <param name="tutorial"></param>
    Tutorial(const Tutorial& tutorial);

    /// <summary>
    /// Title getter
    /// </summary>
    /// <returns>: the title</returns>
    std::string getTitle() const;

    /// <summary>
    /// Duration getter
    /// </summary>
    /// <returns>: the duration</returns>
    std::string getDuration() const;

    /// <summary>
    /// Presenter getter
    /// </summary>
    /// <returns>: the presenter</returns>
    std::string getPresenter() const;

    /// <summary>
    /// like getter
    /// </summary>
    /// <returns>: the likes</returns>
    int getLike() const;

    /// <summary>
    /// Link getter
    /// </summary>
    /// <returns>: the link</returns>
    std::string getLink() const;

    /// <summary>
    /// Title setter
    /// </summary>
    /// <param title="_title"></param>
    void setTitle(std::string _title);

    /// <summary>
    /// Presenter setter
    /// </summary>
    /// <param title="_presenter"></param>
    void setPresenter(std::string _presenter);

    /// <summary>
    /// like setter
    /// </summary>
    /// <param title="_like"></param>
    void setLike(int _like);

    /// <summary>
    /// Link setter
    /// </summary>
    /// <param title="_link"></param>
    void setLink(std::string _link);

    /// <summary>
    /// Duration setter
    /// </summary>
    /// <param title="_duration"></param>
    void setDuration(std::string _duration);

    std::string toString() const;

    /// Tutorial destructor
    ~Tutorial();

    Tutorial& operator=(const Tutorial& tutorial);

    bool operator==(const Tutorial& checkTutorial) const;

    friend std::ostream& operator<<(std::ostream& os, const Tutorial& tutorial);

    friend std::istream& operator>>(std::istream& reader, Tutorial& tutorial);
};
#endif //OOP_LAB4_DOMAIN_H
