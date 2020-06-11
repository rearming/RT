import os
from datetime import datetime
# from pwd import getpwuid

# path = "sources/gui/buttons/rt_button_label.c"
def  create_header(path):
    i = path.rfind('/') + 1
    filename = path[i:]
    author = "dgreat"


    stat = os.stat("sources/gui/buttons/rt_button_label.c")
    ts = int(stat.st_birthtime)
    create = datetime.utcfromtimestamp(ts).strftime('%Y/%m/%d %H:%M:%S')
    ts = int(stat.st_mtime)
    mod = datetime.utcfromtimestamp(ts).strftime('%Y/%m/%d %H:%M:%S')
    print(stat)


    h1 = "/* ************************************************************************** */" + '\n'
    h2 = "/*                                                                            */" + '\n'
    h3 = "/*                                                        :::      ::::::::   */" + '\n'
    h4 = "/*   %s:+:      :+:    :+:   */" % (filename.ljust(51, ' ')) + '\n'
    h5 = "/*                                                    +:+ +:+         +:+     */" + '\n'
    h6 = "/*   By: %s+#+  +:+       +#+        */" % (author + ' <marvin@42.fr>'.ljust(37, ' ')) + '\n'
    h7 = "/*                                                +#+#+#+#+#+   +#+           */" + '\n'
    h8 = "/*   Created: %s by %s#+#    #+#             */" % (create, author.ljust(18, ' ')) + '\n'
    h9 = "/*   Updated: %s by %s###   ########.fr       */" % (mod, author.ljust(17, ' ')) + '\n'
    h10 = "/*                                                                            */" + '\n'
    h11 = "/* ************************************************************************** */"  + '\n'
    h = h1 + h2 + h3 + h4 + h5 + h6 + h7 + h8 + h9 + h10 + h11
    print(h)
    with open(path, 'r+') as f:
        lines = f.readlines()
        f.seek(0)
        f.writelines( [h + '\n']+lines )

create_header('test.c')