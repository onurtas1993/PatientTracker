#pragma once

#ifdef MODEL_EXPORTS
#define MODEL_API __declspec(dllexport)
#else
#define MODEL_API __declspec(dllimport)
#endif

#include <string>

namespace Model
{
	class MODEL_API Patient {
	private:
		std::string _name, _surname, _stay_zone, _in_date, _out_date;
	public:
		Patient(const std::string & name, const std::string & surname, const std::string & stay_zone, const std::string & in_date, const std::string & out_date) :
			_name{ name }, _surname{ surname }, _stay_zone{ stay_zone }, _in_date{ in_date }, _out_date{ out_date } {}

		//Getters
		const std::string& name() const { return _name; }
		const std::string& surname() const { return _surname; }
		const std::string& stayZone() const { return _stay_zone; }
		const std::string& inDate() const { return _in_date; }
		const std::string& outDate() const { return _out_date; }

		//Setters
		void setName(const std::string& value) { _name = value; }
		void setSurname(const std::string& value) { _surname = value; }
		void setStayZone(const std::string& value) { _name = value; }
		void setInDate(const std::string& value) { _name = value; }
		void setOutDate(const std::string& value) { _name = value; }

		operator std::string() const { return _name + " " + _surname; }
	};
}