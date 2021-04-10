#pragma once

struct braket_group
{
private:
	int startIndex;
	bool closed;
public:
	braket_group(int si);
	int getStartIndex() const;
	bool isClosed() const;
	void close();
};
