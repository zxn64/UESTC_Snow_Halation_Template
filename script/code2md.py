import os

# 修改工作目录
os.chdir("../")

# 将代码文件内容包装成代码块写入markdown文件中
def writeCodeFileToMarkDown(md, code):
    # 写入代码块头（C++）
    md.write('\n```c++\n')
    
    # 写入代码内容
    for line in code.readlines():
        md.write(line)
    
    # 写入代码块尾
    md.write('```\n')


# 生成单个专题的markdown文件
def genSingleKindMarkdownFile(name):
    # 打开/创建空的目标文件: src/专题名.md
    md = open(f'markdown/{name}.md', 'w')
    
    # 写入专题名作为一级目录
    md.write(f'# {name}\n')
    path = 'src/' + name
    for item in os.scandir(path):
        if not item.is_file():
            raise Exception(f"具有预期之外的文件类型: {path}/{item.name}")
        
        # 写入模板名作为二级目录
        md.write(f'\n## {item.name}'.removesuffix(".cpp") + '\n')
        
        # 打开代码文件
        code = open(f'{path}/{item.name}', 'r')
        
        writeCodeFileToMarkDown(md, code)
        
        code.close()
    md.close()


# 遍历src文件夹，生成每个专题的独立markdown汇总文件
for item in os.scandir("src"):
    if item.is_dir():
        genSingleKindMarkdownFile(item.name)
    else:
        raise Exception(f"预期之外的文件: src/{item.name}")