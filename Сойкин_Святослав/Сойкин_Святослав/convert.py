import os
import codecs

def try_convert_file(input_path, output_path):
    """Пробует конвертировать файл, используя список кодировок"""
    encodings_to_try = [
        'utf-8', 'utf-8-sig', 'cp1251', 'windows-1251', 
        'iso-8859-1', 'koi8-r', 'cp866', 'mac_cyrillic',
        'utf-16', 'utf-16le', 'utf-16be'
    ]
    
    filename = os.path.basename(input_path)
    
    for encoding in encodings_to_try:
        try:
            with open(input_path, 'r', encoding=encoding, errors='strict') as f:
                content = f.read()
            
            with codecs.open(output_path, 'w', encoding='utf-8-sig') as f:
                f.write(content)
            
            print(f"✓ {filename}: успешно (кодировка: {encoding})")
            return True
            
        except (UnicodeDecodeError, LookupError):
            continue
        except Exception:
            continue
    
    # Последняя попытка: игнорировать ошибки
    try:
        with open(input_path, 'rb') as f:
            binary_data = f.read()
        
        decoded = binary_data.decode('utf-8', errors='ignore')
        
        with codecs.open(output_path, 'w', encoding='utf-8-sig') as f:
            f.write(decoded)
        
        print(f"⚠ {filename}: с потерей данных")
        return True
        
    except Exception:
        print(f"✗ {filename}: не удалось конвертировать")
        return False

def convert_all_files():
    output_folder = "converted_utf8"
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)
    
    current_dir = os.path.dirname(os.path.abspath(__file__))
    
    total = 0
    success = 0
    
    print("Конвертация файлов в UTF-8 BOM...\n")
    
    for filename in os.listdir(current_dir):
        file_path = os.path.join(current_dir, filename)
        
        if os.path.isdir(file_path) or filename.endswith('.py') or filename == output_folder:
            continue
        
        total += 1
        output_path = os.path.join(current_dir, output_folder, filename)
        
        if try_convert_file(file_path, output_path):
            success += 1
    
    print(f"\nГотово! Успешно: {success}/{total} файлов")

if __name__ == "__main__":
    convert_all_files()