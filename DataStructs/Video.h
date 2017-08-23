/*
Header classe concreta Video
*/
#ifndef VIDEO_H
#define VIDEO_H

#include"MultimediaItem.h"
#include<iostream>

class Video: public MultimediaItem{
	private:
		std::string author;
		static bool has_author(const Video&, const std::string&);
		static std::map<std::string, bool (*)(const Video&, const std::string&)> searchMap;

	public:
		std::string getAuthor() const;
		Video(const std::string&, const std::string&, const std::string&, const std::string&, int);
		virtual const std::map<std::string, std::string> readInfo() const;
		virtual void get();
		MultimediaItem* search(const std::string&, const std::string&);
		virtual bool operator==(const Video&);
		virtual ~Video()=default;
};

#endif
