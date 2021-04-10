#include "pch.h"
#include "braket_group.h"

	
braket_group::braket_group(int si) : startIndex(si), closed(false)
	{
	}

	int braket_group::getStartIndex() const
	{
		return startIndex;
	}

	bool braket_group::isClosed() const
	{
		return closed;
	}

	void braket_group::close()
	{
		closed = true;
	}
