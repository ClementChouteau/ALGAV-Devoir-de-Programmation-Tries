#ifndef SIZEABLE_HPP
#define SIZEABLE_HPP

class Sizeable {
public:
	virtual ~Sizeable() {}
	virtual long tailleEnMemoire() const = 0;
};

#endif // SIZEABLE_HPP
