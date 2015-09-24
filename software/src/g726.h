
#ifndef _VOIP_G726_H
#define _VOIP_G726_H

/*
 * The following is the definition of the state structure
 * used by the G.721/G.723 encoder and decoder to preserve their internal
 * state between successive calls.  The meanings of the majority
 * of the state structure fields are explained in detail in the
 * CCITT Recommendation G.721.  The field names are essentially indentical
 * to variable names in the bit level description of the coding algorithm
 * included in this Recommendation.
 */
struct g726_state {
	long yl;		/* Locked or steady state step size multiplier. */
	short yu;		/* Unlocked or non-steady state step size multiplier. */
	short dms;		/* Short term energy estimate. */
	short dml;		/* Long term energy estimate. */
	short ap;		/* Linear weighting coefficient of 'yl' and 'yu'. */

	short a[2];		/* Coefficients of pole portion of prediction filter. */
	short b[6];		/* Coefficients of zero portion of prediction filter. */
	short pk[2];	/*
					 * Signs of previous two samples of a partially
					 * reconstructed signal.
					 */
	short dq[6];	/*
					 * Previous 6 samples of the quantized difference
					 * signal represented in an internal floating point
					 * format.
					 */
	short sr[2];	/*
					 * Previous 2 samples of the quantized difference
					 * signal represented in an internal floating point
					 * format.
					 */
	char td;		/* delayed tone detect, new in 1988 version */
};


void g726_init_state(struct g726_state *state_ptr);
int g726_decode(int	i, struct g726_state *state_ptr);
int g726_encode(int sl, struct g726_state *state_ptr);


#endif
