#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include<iostream>
#include<string>

class Exception {
public:
	Exception();
	~Exception();
	virtual std::string GetMessage() const = 0;
};

class NonFloatInMatrixException : public Exception {
public:
	NonFloatInMatrixException();
	~NonFloatInMatrixException();

	std::string GetMessage() const;
};

class NonSymmetricMatrixException : public Exception {
public:
	NonSymmetricMatrixException();
	~NonSymmetricMatrixException();

	std::string GetMessage() const;
};

class PositiveDefiniteMatrixException : public Exception {
public:
	PositiveDefiniteMatrixException();
	~PositiveDefiniteMatrixException();

	std::string GetMessage() const;
};

class FileReadException : public Exception {
public:
	FileReadException();
	~FileReadException();

	std::string GetMessage() const;
};

#endif // !EXCEPTIONS_HPP