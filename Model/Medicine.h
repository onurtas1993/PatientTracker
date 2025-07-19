#pragma once

#ifdef MODEL_EXPORTS
#define MODEL_API __declspec(dllexport)
#else
#define MODEL_API __declspec(dllimport)
#endif

#include <string>

namespace Model
{
	class MODEL_API Medicine {
	private:
		std::string _receipt_number, _name, _start_date, _expiration_date;
	public:
		Medicine(const std::string & receipt_number, const std::string & name, const std::string & start_date, const std::string & expiration_date) :
			_receipt_number{ receipt_number }, _name{ name }, _start_date{ start_date }, _expiration_date{ expiration_date } {}

		//Getters
		const std::string& receiptNumber() const { return _receipt_number; }
		const std::string& name() const { return _name; }
		const std::string& startDate() const { return _start_date; }
		const std::string& expirationDate() const { return _expiration_date; }

		//Setters
		void setReceiptNumber(const std::string& value) { _receipt_number = value; }
		void setName(const std::string& value) { _name = value; }
		void setStartDate(const std::string& value) { _start_date = value; }
		void setExpirationDate(const std::string& value) { _expiration_date = value; }
	};
}