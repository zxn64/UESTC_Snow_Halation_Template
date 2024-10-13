import os

# 修改工作目录
os.chdir("../")

typ = open('typst/Template.typ', 'w')

header = \
'''#align(center + horizon, text(size: 32pt, heading(level: 1, outlined: false,  `UESTC_SNOW_HALATION's TEMPLATE`)))

#pagebreak()
#outline()
#pagebreak()

#counter(page).update(1)
#set page(numbering: "1 / 1")
'''

heading = [('# ', '== '), ('## ', '=== ')]


# 添加封面，目录等信息
typ.write(header)

for md_name in os.scandir('markdown'):
    typ.write('\n')
    md = open(f'markdown/{md_name.name}', 'r')
    for line in md.readlines():
        for head, new_head in heading:
            if line.startswith(head):
                line = new_head + line.removeprefix(head)
                break
        typ.write(line)
