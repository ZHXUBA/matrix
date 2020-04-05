#ifndef TOOLS_H
#define TOOLS_H

namespace tools {

	// �ж����������ǲ���һ��
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

