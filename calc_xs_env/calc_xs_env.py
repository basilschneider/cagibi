#!/usr/bin/env python2

# Read in cross sections from CTEQ6.6 and MSTW2008nlo90cl including
# uncertainties and spit out cross section envelope, according to
# https://arxiv.org/abs/1206.2892

from sys import argv
from math import sqrt

def get_values(f):
    with open(f, 'r') as f:
        lines = f.read().splitlines()
        line = lines[-1]
    return line.split()

if __name__ == '__main__':

    try:
        f_cteq = argv[1]
        f_mstw = argv[2]
    except IndexError:
        raise IndexError('Need two positional arguments')

    l_cteq = get_values(f_cteq)
    l_mstw = get_values(f_mstw)

    cteq_mass = float(l_cteq[0])
    cteq_nll = float(l_cteq[9]) * 1000.
    cteq_pdf_dn = float(l_cteq[10]) / 100. * cteq_nll
    cteq_pdf_up = float(l_cteq[11]) / 100. * cteq_nll
    cteq_sca_dn = float(l_cteq[12]) / 100. * cteq_nll
    cteq_sca_up = float(l_cteq[13]) / 100. * cteq_nll

    mstw_mass = float(l_mstw[0])
    mstw_nll = float(l_mstw[9]) * 1000.
    mstw_pdf_dn = float(l_mstw[10]) / 100. * cteq_nll
    mstw_pdf_up = float(l_mstw[11]) / 100. * cteq_nll
    mstw_sca_dn = float(l_mstw[12]) / 100. * cteq_nll
    mstw_sca_up = float(l_mstw[13]) / 100. * cteq_nll

    cteq_up = sqrt(pow(cteq_pdf_up, 2) + pow(cteq_sca_up, 2))
    cteq_dn = sqrt(pow(cteq_pdf_dn, 2) + pow(cteq_sca_dn, 2))

    mstw_up = sqrt(pow(mstw_pdf_up, 2) + pow(mstw_sca_up, 2))
    mstw_dn = sqrt(pow(mstw_pdf_dn, 2) + pow(mstw_sca_dn, 2))

    env_u = max(cteq_nll + cteq_up, mstw_nll + mstw_up)
    env_l = min(cteq_nll - cteq_dn, mstw_nll - mstw_dn)

    xs = (env_u + env_l)/2
    xs_unc = (env_u - env_l)/2

    print 'Mass: {}'.format(cteq_mass)
    print 'Cross section: {}'.format(xs)
    print 'Uncertainty: {}'.format(xs_unc)
