#pragma once
#ifndef TOOLS_H
#define TOOLS_H

namespace tools {

	// 判断两个类型是不是一种
	template<class T1, class T2>
	struct sameType {
		bool operator() () {
			return false;
		}
	};
	template<class T>
	struct sameType<T, T> {
		bool operator() () {
			return true;
		}
	};

} // end of namespace tools

#endif // !TOOLS_H

