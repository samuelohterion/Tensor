#ifndef TERM_HPP
#define TERM_HPP

#include <iomanip>
#include <string>
#include <sstream>
//#include "idx.h"

template< typename T >
class Tree {

	public:

		Tree() {

		}

		virtual
		~Tree() {

		}

	public:

		virtual Tree< T >
		*cpy() const = 0;

		std::string
		str(std::size_t const &p_width = 0) const {

			std::stringstream
			ss;

			if(p_width) {

				ss << std::setw(p_width) << val();

				return ss.str();
			}

			ss << val();

			return ss.str();
		}

		virtual T
		val() const = 0;
};

template< typename T >
class TreeValue :
public Tree< T > {

	public:

		TreeValue(T const &p_val) :
		Tree< T >(),
		__val(p_val) {

		}

		~TreeValue() {

		}

	private:

		T
		__val;

	public:

		Tree< T >
		*cpy() const {

			return new TreeValue< T >(__val);
		}

		TreeValue< T >
		&set(T const &p_val) {

			__val = p_val;

			return *this;
		}

		T
		val() const {

			return __val;
		}
};

template< typename T, typename T2 >
class TreeCast :
public Tree< T > {

	public:

		TreeCast(Tree< T2 > *p_tree) :
		Tree< T >(),
		__from(p_tree) {

		}

		~TreeCast() {

			delete __from;
		}

	private:

		Tree< T2 >
		*__from;

	public:

		Tree< T >
		*cpy() const {

			return new TreeCast< T, T2 >(__from->cpy());
		}

		T
		val() const {

			return __from->val();
		}
};

template< typename T >
class TreeQueue :
public Tree< T > {

	public:

		TreeQueue(Tree< T > *p_arg) :
		Tree< T >(),
		_arg(p_arg) {

		}

		~TreeQueue() {

			delete _arg;
		}

	protected:

		Tree< T >
		*_arg;

	public:

		Tree< T >
		*arg(bool p_copy = false) const {

			return p_copy ? _arg->cpy() : _arg;
		}
};

template< typename T >
class TreeBranch :
public Tree< T > {

	public:

		TreeBranch(Tree< T > *p_lhs, Tree< T > *p_rhs) :
		Tree< T >(),
		_lhs(p_lhs),
		_rhs(p_rhs) {

		}

		~TreeBranch() {

			delete _lhs;
			delete _rhs;
		}

	protected:

		Tree< T >
		*_lhs,
		*_rhs;

	public:

		Tree< T >
		*lhs(bool p_copy = false) const {

			return p_copy ? _lhs->cpy() : _lhs;
		}

		Tree< T >
		*rhs(bool p_copy = false) const {

			return p_copy ? _rhs->cpy() : _rhs;
		}
};

/*
template< typename T >
class TreeArithmeticNeg :
public TreeQueue< T > {

	public:

		TreeArithmeticNeg(Tree< T > *p_arg) :
		TreeQueue< T >(p_arg) {

		}

		~TreeArithmeticNeg() {

		}

	public:


		Tree< T >
		*cpy() const {

			return new TreeArithmeticNeg(this->arg(true));
		}

		T
		val() const {

			return -this->arg()->val();
		}
};

template< typename T >
class TreeLogicalNeg :
public TreeQueue< T > {

	public:

		TreeLogicalNeg(Tree< T > *p_arg) :
		TreeQueue< T >(p_arg) {

		}

		~TreeLogicalNeg() {

		}

	public:


		Tree< T >
		*cpy() const {

			return new TreeLogicalNeg(this->arg(true));
		}

		T
		val() const {

			return ~this->arg()->val();
		}
};
*/
/*
template< typename T >
class TreeSum :
public TreeBranch< T > {

	public:

		TreeSum(Tree< T > *p_lhs, Tree< T > *p_rhs) :
		TreeBranch< T >(p_lhs, p_rhs) {

		}

		~TreeSum() {

		}

	public:


		Tree< T >
		*cpy() const {

			return new TreeSum(this->lhs(true), this->rhs(true));
		}

		T
		val() const {

			return this->lhs()->val() + this->rhs()->val();
		}
};

template< typename T >
class TreeDif :
public TreeBranch< T > {

	public:

		TreeDif(Tree< T > *p_lhs, Tree< T > *p_rhs) :
		TreeBranch< T >(p_lhs, p_rhs) {

		}

		~TreeDif() {

		}

	public:


		Tree< T >
		*cpy() const {

			return new TreeDif(this->lhs(true), this->rhs(true));
		}

		T
		val() const {

			return this->lhs()->val() - this->rhs()->val();
		}
};

template< typename T >
class TreeMul :
public TreeBranch< T > {

	public:

		TreeMul(Tree< T > *p_lhs, Tree< T > *p_rhs) :
		TreeBranch< T >(p_lhs, p_rhs) {

		}

		~TreeMul() {

		}

	public:


		Tree< T >
		*cpy() const {

			return new TreeMul(this->lhs(true), this->rhs(true));
		}

		T
		val() const {

			return this->lhs()->val() * this->rhs()->val();
		}
};

template< typename T >
class TreeDiv :
public TreeBranch< T > {

	public:

		TreeDiv(Tree< T > *p_lhs, Tree< T > *p_rhs) :
		TreeBranch< T >(p_lhs, p_rhs) {

		}

		~TreeDiv() {

		}

	public:


		Tree< T >
		*cpy() const {

			return new TreeDiv(this->lhs(true), this->rhs(true));
		}

		T
		val() const {

			return this->lhs()->val() / this->rhs()->val();
		}
};
*/
/*
template< typename T >
class TreeArithmeticNeg :
public TreeQueue< T > {

	public:

		TreeArithmeticNeg(Tree< T > *p_arg) :
		TreeQueue< T >(p_arg) {

		}

		~TreeArithmeticNeg() {

		}

	public:


		Tree< T >
		*cpy() const {

			return new TreeArithmeticNeg(this->arg(true));
		}

		T
		val() const {

			return -this->arg()->val();
		}
};
*/

template< typename T, class FUNC >
class TreeUnOp_DASA :
public TreeQueue< T > {

	public:

		TreeUnOp_DASA(Tree< T > *p_arg) :
		TreeQueue< T >(p_arg) {

		}

		~TreeUnOp_DASA() {

		}

	public:


		Tree< T >
		*cpy() const {

			return new TreeUnOp_DASA< T, FUNC >(this->arg(true));
		}

		T
		val() const {

			return FUNC()(this->arg()->val());
		}
};

template< typename T, class FUNC >
class TreeBinOP_DALARA:
public TreeBranch< T > {

	public:

		TreeBinOP_DALARA(Tree< T > *p_lhs, Tree< T > *p_rhs) :
		TreeBranch< T >(p_lhs, p_rhs) {
		}

		~TreeBinOP_DALARA() {
		}

	public:

		Tree< T >
		*cpy() const {

			return new TreeBinOP_DALARA< T, FUNC >(this->lhs(true), this->rhs(true));
		}

		T
		val() const {

			return FUNC()(this->lhs()->val(), this->rhs()->val());
		}
};

template< typename T >
class Term {

	public:

		Term() :
		__tree(0) {

		}

		Term(Tree< T > *p_tree) :
		__tree(p_tree) {

		}

		template< typename T2 >
		Term(Term< T2 > const &p_term) :
		__tree(new TreeCast< T, T2 >(p_term.cpy())) {

		}

		~Term() {

			delete __tree;
		}

	private:

		Tree< T >
		*__tree;

	public:

		Tree< T >
		*cpy() const {

			return __tree->cpy();
		}

		Tree< T >
		*tree() const {

			return __tree;
		}

		T
		val() const {

			return __tree->val();
		}

		std::string
		str(std::size_t const &p_width = 0) const {

			return __tree->str(p_width);
		}

	public:

		operator T() {

			return val();
		}

		Term< T >
		&operator =(Term< T > &p_term) {

			delete __tree;

			__tree = p_term.cpy();
		}

		Term< T >
		operator +() const {

			return Term< T >(this->cpy());
		}

		Term< T >
		operator -() const {

			return Term< T >(new TreeUnOp_DASA< T, std::negate< T > >(this->cpy()));
		}

		Term< T >
		operator ~() const {

			return Term< T >(new TreeUnOp_DASA< T, std::bit_not< T > >(this->cpy()));
		}

		Term< T >
		operator !() const {

			return Term< T >(new TreeUnOp_DASA< T, std::logical_not< T > >(this->cpy()));
		}


		Term< T >
		operator <(Term< T > const &p_term) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::less< T > >(this->cpy(), p_term.cpy()));
		}

		Term< T >
		operator <(T const &p_val) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::less< T > >(this->cpy(), new TreeValue< T >(p_val)));
		}

		Term< T >
		operator <=(Term< T > const &p_term) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::less_equal< T > >(this->cpy(), p_term.cpy()));
		}

		Term< T >
		operator <=(T const &p_val) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::less_equal< T > >(this->cpy(), new TreeValue< T >(p_val)));
		}

		Term< T >
		operator ==(Term< T > const &p_term) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::equal_to< T > >(this->cpy(), p_term.cpy()));
		}

		Term< T >
		operator ==(T const &p_val) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::equal_to< T > >(this->cpy(), new TreeValue< T >(p_val)));
		}

		Term< T >
		operator !=(Term< T > const &p_term) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::not_equal_to< T > >(this->cpy(), p_term.cpy()));
		}

		Term< T >
		operator !=(T const &p_val) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::not_equal_to< T > >(this->cpy(), new TreeValue< T >(p_val)));
		}

		Term< T >
		operator >=(Term< T > const &p_term) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::greater_equal< T > >(this->cpy(), p_term.cpy()));
		}

		Term< T >
		operator >=(T const &p_val) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::greater_equal< T > >(this->cpy(), new TreeValue< T >(p_val)));
		}

		Term< T >
		operator >(Term< T > const &p_term) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::greater< T > >(this->cpy(), p_term.cpy()));
		}

		Term< T >
		operator >(T const &p_val) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::greater< T > >(this->cpy(), new TreeValue< T >(p_val)));
		}


		Term< T >
		operator &(Term< T > const &p_term) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::bit_and< T > >(this->cpy(), p_term.cpy()));
		}

		Term< T >
		operator &(T const &p_val) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::bit_and< T > >(this->cpy(), new TreeValue< T >(p_val)));
		}

		Term< T >
		operator |(Term< T > const &p_term) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::bit_or< T > >(this->cpy(), p_term.cpy()));
		}

		Term< T >
		operator |(T const &p_val) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::bit_or< T > >(this->cpy(), new TreeValue< T >(p_val)));
		}

		Term< T >
		operator ^(Term< T > const &p_term) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::bit_xor< T > >(this->cpy(), p_term.cpy()));
		}

		Term< T >
		operator ^(T const &p_val) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::bit_xor< T > >(this->cpy(), new TreeValue< T >(p_val)));
		}


		Term< T >
		operator &&(Term< T > const &p_term) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::logical_and< T > >(this->cpy(), p_term.cpy()));
		}

		Term< T >
		operator &&(T const &p_val) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::logical_and< T > >(this->cpy(), new TreeValue< T >(p_val)));
		}

		Term< T >
		operator ||(Term< T > const &p_term) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::logical_or< T > >(this->cpy(), p_term.cpy()));
		}

		Term< T >
		operator ||(T const &p_val) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::logical_or< T > >(this->cpy(), new TreeValue< T >(p_val)));
		}




		Term< T >
		operator +(Term< T > const &p_term) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::plus< T > >(this->cpy(), p_term.cpy()));
		}

		Term< T >
		operator +(T const &p_val) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::plus< T > >(this->cpy(), new TreeValue< T >(p_val)));
		}

		Term< T >
		operator -(Term< T > const &p_term) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::minus< T > >(this->cpy(), p_term.cpy()));
		}

		Term< T >
		operator -(T const &p_val) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::minus< T > >(this->cpy(), new TreeValue< T >(p_val)));
		}

		Term< T >
		operator *(Term< T > const &p_term) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::multiplies< T > >(this->cpy(), p_term.cpy()));
		}

		Term< T >
		operator *(T const &p_val) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::multiplies< T > >(this->cpy(), new TreeValue< T >(p_val)));
		}

		Term< T >
		operator /(Term< T > const &p_term) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::divides< T > >(this->cpy(), p_term.cpy()));
		}

		Term< T >
		operator /(T const &p_val) const {

			return Term< T >(new TreeBinOP_DALARA< T, std::divides< T > >(this->cpy(), new TreeValue< T >(p_val)));
		}
};

template< typename T >
Term< T >
operator <(T const &p_val, Term< T > const &p_term) {

	return Term< T >(new TreeBinOP_DALARA< T, std::less< T > >(new TreeValue< T >(p_val), p_term.cpy()));
}

template< typename T >
Term< T >
operator <=(T const &p_val, Term< T > const &p_term) {

	return Term< T >(new TreeBinOP_DALARA< T, std::less_equal< T > >(new TreeValue< T >(p_val), p_term.cpy()));
}

template< typename T >
Term< T >
operator ==(T const &p_val, Term< T > const &p_term) {

	return Term< T >(new TreeBinOP_DALARA< T, std::equal_to< T > >(new TreeValue< T >(p_val), p_term.cpy()));
}

template< typename T >
Term< T >
operator !=(T const &p_val, Term< T > const &p_term) {

	return Term< T >(new TreeBinOP_DALARA< T, std::not_equal_to< T > >(new TreeValue< T >(p_val), p_term.cpy()));
}

template< typename T >
Term< T >
operator >=(T const &p_val, Term< T > const &p_term) {

	return Term< T >(new TreeBinOP_DALARA< T, std::greater_equal< T > >(new TreeValue< T >(p_val), p_term.cpy()));
}

template< typename T >
Term< T >
operator >(T const &p_val, Term< T > const &p_term) {

	return Term< T >(new TreeBinOP_DALARA< T, std::greater< T > >(new TreeValue< T >(p_val), p_term.cpy()));
}

template< typename T >
Term< T >
operator &(T const &p_val, Term< T > const &p_term) {

	return Term< T >(new TreeBinOP_DALARA< T, std::bit_and< T > >(new TreeValue< T >(p_val), p_term.cpy()));
}

template< typename T >
Term< T >
operator |(T const &p_val, Term< T > const &p_term) {

	return Term< T >(new TreeBinOP_DALARA< T, std::bit_or< T > >(new TreeValue< T >(p_val), p_term.cpy()));
}

template< typename T >
Term< T >
operator ^(T const &p_val, Term< T > const &p_term) {

	return Term< T >(new TreeBinOP_DALARA< T, std::bit_xor< T > >(new TreeValue< T >(p_val), p_term.cpy()));
}

template< typename T >
Term< T >
operator &&(T const &p_val, Term< T > const &p_term) {

	return Term< T >(new TreeBinOP_DALARA< T, std::logical_and< T > >(new TreeValue< T >(p_val), p_term.cpy()));
}

template< typename T >
Term< T >
operator ||(T const &p_val, Term< T > const &p_term) {

	return Term< T >(new TreeBinOP_DALARA< T, std::logical_or< T > >(new TreeValue< T >(p_val), p_term.cpy()));
}

template< typename T >
Term< T >
operator +(T const &p_val, Term< T > const &p_term) {

	return Term< T >(new TreeBinOP_DALARA< T, std::plus< T > >(new TreeValue< T >(p_val), p_term.cpy()));
}

template< typename T >
Term< T >
operator -(T const &p_val, Term< T > const &p_term) {

	return Term< T >(new TreeBinOP_DALARA< T, std::minus< T > >(new TreeValue< T >(p_val), p_term.cpy()));
}

template< typename T >
Term< T >
operator *(T const &p_val, Term< T > const &p_term) {

	return Term< T >(new TreeBinOP_DALARA< T, std::multiplies< T > >(new TreeValue< T >(p_val), p_term.cpy()));
}

template< typename T >
Term< T >
operator /(T const &p_val, Term< T > const &p_term) {

	return Term< T >(new TreeBinOP_DALARA< T, std::divides< T > >(new TreeValue< T >(p_val), p_term.cpy()));
}

#endif // TERM_HPP
