import os
from fontTools.ttLib import TTFont


def modify_font_family_name(font_path, new_family_name, output_path):
    # 打开TTF文件
    font = TTFont(font_path)

    # 修改字族名字
    name_record = font["name"]
    for record in name_record.names:
        if record.nameID == 1:  # 1 是字族名字ID
            if record.platformID == 3 and record.platEncID == 1:
                # Unicode 编码
                print(
                    f"Unicode: {record.string.decode('utf-16-be')} -> {new_family_name}"
                )
                record.string = new_family_name.encode("utf-16-be")
            elif record.platformID == 1 and record.platEncID == 0:
                # ASCII 编码
                print(f"ASCII: {record.string.decode('ascii')} -> {new_family_name}")
                record.string = new_family_name.encode("ascii")
            else:
                print(
                    f"Unknown: {record.nameID}, {record.platformID}, {record.platEncID}, {record.langID}"
                )
                exit(1)

    # 保存修改后的TTF文件
    font.save(output_path)
    print(f"new font family name: {new_family_name} save to {output_path}")


if __name__ == "__main__":
    __old_font_file = "iconfont/iconfont.ttf"
    __new_font_file = "iconfont/iconfont.ttf"
    __new_family_name = "lzl-iconfont"

    __curr_dir = os.path.dirname(os.path.abspath(__file__))
    __font_path = os.path.join(__curr_dir, __old_font_file)
    __output_path = os.path.join(__curr_dir, __new_font_file)
    modify_font_family_name(__font_path, __new_family_name, __output_path)
