#!/usr/bin/python
#coding=utf-8

# for 1.10	from __future__ imports must occur at the beginning of the file
from __future__ import division	# ����ģ���е�__future__������������ȷ��2.1֮ǰ�汾��Python������������һЩ�µ��������ԣ���������ȱ������ضϡ�

# ��һ�� �ı�

# 1.1-ÿ�δ���һ���ַ�
def fun1_1_1(char):
	return char,	# ���Ӷ��ű�ʾ����һ���ַ����Ӷ��ű�ʾ����Ԫ��

def chapter1_1():
	str = 'Hello World'
	print list(str)	# ���ַ�����ֳ�list
	print ''.join(list(str))	# list(str)�ķ����������list���Ϊ�ַ���

	for char in str:	# ѭ����ȡ�ַ�����ÿ���ַ�
		print char,	# printĬ������س������Ӷ��ſɱ�������س���
	print ''

	result = [i for i in str]	# ����for����ʼ��list
	print result

	result = map(fun1_1_1, str)	# ÿ��ȡһ���ַ�������һ�κ���
	print result	# ���Ϊÿ��fun1_1_1����ֵ��list
	result = map(lambda x : (x,), str)	# ������������������ʵ��
	print result	# ���Ϊÿ��fun1_1_1����ֵ��list

	pass

# 1.2-�ַ����ַ�ֵ֮���ת��
def chapter1_2():
	print ord('a')	# ���ַ�ת�������Ӧ��ASCII��
	print chr(97)	# �����鿴��ASCII�룬������ת��Ϊ�ַ�

	# \u2020Ҳ����Ϊ���Ļ�������Unicode�ַ�
	print ord(u'\u2020')	# ��Unicode�ַ�ת��ΪUnicode����
	print unichr(8824)	# ��Unicode����ת��ΪUnicode�ַ�

	print repr(chr(97))	# chr������ת����ASCII�ַ�
	print repr(str(97))	# str������ֱ��ת�������Ӧ���ַ���

	print map(ord, 'hello')	# ʹ��map���ַ���ת����ΪASCII��������
	print ''.join(map(chr, range(97, 123)))	# ��ӡ26����ĸ

	pass

# 1.3-����һ�������Ƿ������ַ���
def isStringLike(anobj):
	'''
	python����ɫ֮һ���Ǹ����Լ���Ԥ��ȥִ�������ڴ˹����м�������쳣��
	����һ�������Ĵ���ʽ����������ȡ�º�ԭ���ܱ����ȵõ����Ҫ���׵Ķࡱ
	'''

	try: anobj + ''	# ͨ���޸�try�Ĳ��֣����Լ�������ַ�������
	except: return False
	else: return True

def chapter1_3():
	string = 'Hello World'
	print isinstance(string, basestring)	# basestring��str��unicode�����ĸ��Ĺ�ͬ����
	string = 'Hello World'
	print isinstance(string, str)	# str���������Ϊ���������޷�����Ϊ����ʹ��
	string = 'Hello World'
	print isinstance(string, unicode)
	string = u'Hello World'
	print isinstance(string, unicode)

	print type(string) is type(u'')	# ��Ȼ���ַ���Ҳ���Խ������Ͳ��ԣ��������ַ����ǳ���⣬�����޷��ж��Զ�������
	print isStringLike(string)	# ���ַ�����isinstanceҪ���Ķ࣬����ȴ���������ַ������͵�ʵ��

	pass

# 1.4-�ַ�������
def chapter1_4():
	'''
	ljust & r rjust: �������Ҷ��룬������ʾ��䷶Χ������ַ�Ĭ��Ϊ�ո�
	center: ���У�������ʾ��䷶Χ������ַ�
	'''

	print '|', 'hej'.ljust(20), '|', 'hej'.rjust(20), '|', 'hej'.center(20, '+'), '|'

	pass

# 1.5-ȥ���ַ������˵Ŀո�
def chapter1_5():
	'''
	lstrip, rstrip, strip
	�ֱ�ȥ�����Һ����˵�ָ���ַ���Ĭ��Ϊ�ո�
	����Ҳ����ָ���ַ��б�
	'''

	print '|', '+hej+'.lstrip('+'), '|', '+hej+'.rstrip('+'), '|', '+hej+'.strip('+'), '|'
	print '|', 'xyxxyy hejyx yyx'.strip('xy'), '|'

	pass

# 1.6-�ϲ��ַ���
def chapter1_6():
	'''
	python���ַ����޷��ı䣬ֻ�ܴ����µ��ַ��������ԣ����ִ���ʽ�м������٣��ٶȾ�Խ��
	�ɴ�������'+'�������������ҪN-1���м�������join��ʽ�����ģ�ֻ��Ҫһ���м�buf
	�����ַ���ƴ�������������Ƽ�ʹ�ø�ʽ��������ƣ��ɶ���ǿ������չ��ǿ�������˺ܶ�����ֵ�str()ת����������Ч����Ҳ��������
	'''
	print 'foo'+'bar'	# '+'���������ַ������ͼ�Ϊ���Ӳ�������Ȼ'+='Ҳ��֧�ֵ�
	print 'foo','bar'	# ���ŵĵ�Ĭ�ϴ���Ϊ�ո�ָ�
	print '%s%s' % ('foo', 'bar')	# ��C���Եĸ�ʽ�����
	import operator
	print reduce(operator.add, ['x','y','z'], 'init')	# reduce�ĵ���������Ϊ��ʼ��ֵ��Ϊ��ѡ����
	print ''.join(['foo', 'bar'])	# ���ַ���������У�Ȼ���������е�Ԫ��Ҳ���Դﵽ�ַ������ӵ�Ч��
	print 'foo'.join('bar')	# �����÷��Ǵ�ģ����Ϊ��bfooafoor��join��'bar'��Ϊlist����'foo'Ϊ�ָ����������

	pass

# 1.7-���ַ������ַ�����ʷ�ת
def chapter1_7():
	# ���ַ�ת
	print 'hello'[::-1]

	wlist = list('hello')
	wlist.reverse()	# list��reverse����ֻ��תlistԪ�أ�û�з���ֵ
	print ''.join(wlist)
	print ''.join(list('hello')[::-1])	# ����������һ�б�ʾ

	print reduce(lambda x,y: y+x, 'hello')

	# ��ʷ�ת
	wlist = 'hello world'.split()
	wlist.reverse()
	print ' '.join(wlist)
	print ' '.join(('hello world').split()[::-1])	# ����������һ�б�ʾ

	import re	# ������ʽ��ʽ
	wlist = re.split(r'(\s+)', 'hello world')
	wlist.reverse()
	print ''.join(wlist)	# ���򽫿ո�Ҳ��Ϊ��תԪ�أ���join��ʱ��������ʹ�ÿո���Ϊ���ӷ�
	print ''.join(re.split(r'(\s+)', 'hello world')[::-1])	# ����������һ�б�ʾ

	pass

# 1.8-����ַ������Ƿ����ĳ�ַ������е��ַ�
def containsAny(seq, aset):	# �ж�aset���Ƿ����seq�е��ַ�����
	''' �������seq�Ƿ���aset�е��� '''
	for c in seq:
		if c in aset: return True
	return False

def containsOnly(seq, aset):
	''' �������seq�Ƿ�ֻ��aset�е��� '''
	for c in seq:
		if c not in aset: return False
	return True

import string
notrans = string.maketrans('', '')	# maketrans: make map of attr1 to attr2
def containsAny2(astr, strset):
	return len(strset) != len(strset.translate(notrans, astr))	# translate: delete set of attr2, and translate by map table(attr1)
def containsAll(astr, strset):
	return not strset.translate(notrans, astr)

def chapter1_8():
	print 'abc' in '123zxcabcqweasd'	# in �ؼ��ֿ��Խ����Ӵ����

	print containsAny('abc', '123zxcabcqweasd')
	print set( '123zxcabcqweasd').intersection('abc')	# ʹ��build-in��set��������ʵ��containsAny�Ĺ���
	print bool(set( '123zxcabcqweasd').intersection('abc'))	# ������ȫ���ķ����������Ϊ���жϾ�̫���ˣ�����ġ���·�������ҵ�һ���ͷ��أ���Կ�Ķ�

	print containsAny('abc', 'acbac')
	print set('acbacd').difference('abc')	# set.difference()��ʾȡ�
	print not set('acbac').difference('abc')	# ʹ��build-in��set��������ʵ��containsOnly�Ĺ���

	# ��������ٶȲ�������������ã�����ͨ���Բ�������ķ�������Ҫ��astr��strset������ͨ�ַ���������Unicode�ַ���������
	print containsAny2('abc', 'acbac')
	print containsAll('abc', 'acbacd')

	pass

# 1.9-���ַ�����translate������ʹ��
import string
def translator(frm='', to='', delete='', keep=None):	# �����޷�����ͬʱָ��delete��keep���������Ϊ����û�б�Ҫ��ôָ��
	if len(to) == 1:
		to = to * len(frm)
	trans = string.maketrans(frm, to)
	if keep is not None:
		allchars = string.maketrans('', '')	# maketrans�ķ���ֵ����Ϊ�ַ���
		delete = allchars.translate(allchars, keep.translate(allchars,delete))	# ��keep֮����ַ��趨Ϊdelete
	def translate(s):
		return s.translate(trans, delete)
	return translate

def chapter1_9():
	digits_only = translator(keep=string.digits)
	print digits_only('Chris Perkings : 224-7992')

	no_digits = translator(delete=string.digits)
	print no_digits('Chris Perkings : 224-7992')

	digits_to_hash = translator(frm=string.digits, to='#')
	print digits_to_hash('Chris Perkings : 224-7992')

	# ͬʱָ��delete��keepû���κ����壬���߶�ָ��ʱ����ѡ�������һ�������׳��쳣
	trans = translator(delete='abcd', keep='cdef')
	print trans('abcdefg')

	pass

# �����ַ����в�����ָ�����ϵ��ַ�
import string
# ���������ַ��Ŀɸ��õ��ַ���������������Ϊһ�������ָ�������跭�롱
allchars = string.maketrans('', '')	# ��Ϊȫ�ֱ����������˶�ο����������ڴ濪�������Ч��
def makefilter(keep):
	'''
	����һ���������˷��غ�������һ���ַ�����Ϊ���� 
	�������ַ�����һ�����ֿ������˿���ֻ������keep
	�е��ַ���ע��keep������һ����ͨ�ַ���
	'''

	# ����һ�������в���keep�е��ַ���ɵ��ַ�����
	# keep�Ĳ�����������������Ҫɾ�����ַ�
	delchars = allchars.translate(allchars, keep)

	# ���ɲ�������Ҫ�Ĺ��˺�������Ϊ�հ���
	def thefilter(s):
		return s.translate(allchars, delchars)
	return thefilter

	# ������Ƕ�������صĵ�����ʽ
	return lambda s: s.translate(allchars, delchars)

import sets
class Keeper(object):
	def __init__(self, keep):
		self.keep = sets.Set(map(ord, keep))
	def __getitem__(self, n):	# __getitem__(self,key)   ʹ��x[key]������������ʱ����á�
		if n not in self.keep:
			return None
		return unichr(n)
	def __call__(self, s):		# __call__(self, *args)   called when an instance is called as function.
		return unicode(s).translate(self)

makefilter2 = Keeper

def chapter1_10():
	just_vowels = makefilter('aeiouy')
	print just_vowels('four score and seven years ago')	# output: ouoeaeeyeaao
	print just_vowels('tiger, tiger burning bright')	# output: ieieuii
	# ���������ĵ���ʵ��
	print makefilter('aeiouy')('four score and seven years ago')
	print makefilter('aeiouy')('tiger, tiger burning bright')

	# ��ֱ�Ӵ����ַ����������У�string���translate���Ǳ�setҪ��һЩ
	# ���ź����ǲ���ͨ�ã�����������������Unicode�ַ���������
	instr = u"���������ƣ�Liberal democracy��������������21���͵�������ʽ������ȡ�˴��������ƣ�������ѡ�������������ʹ����Ȩ������Ȩ�����ܵ����εļල������"
	trans_table = dict([[ord(char), u"*"] for char in u"����"])	# unicode�ַ���ֻ������dict��Ϊӳ���
	print trans_table
	filtered = unicode.translate(instr, trans_table)	# translate֧������dict��Ϊ����������������maketrans�ķ���ֵ
	print filtered

	# ���õİ취�ǣ���дһ���򵥵Ĵ���ʵ����__getitem__��������
	just_vowels = makefilter2('aeiouy')
	print just_vowels(u'four score and seven years ago')	# output: ouoeaeeyeaao
	print just_vowels(u'tiger, tiger burning bright')	# output: ieieuii

	pass

# ���һ���ַ������ı����Ƕ�����
# from __future__ import division at head of file
import string
text_characters = ''.join(map(chr, range(32, 127))) + '\n\r\t\b'
_null_trans = string.maketrans('','')
def istext(s, text_characters=text_characters, threshold=0.30):
	# ��s�����˿�ֵ���������ı�
	if '\0' in s:
		return False
	# һ�����ա��ַ����ǡ��ı���������һ�����ܵ��ֺܺ����ѡ��)
	if not s:
		return True
	# ���s���ɷ��ı��ַ����ɵ��Ӵ�
	t = s.translate(_null_trans, text_characters)
	# ���������30%���ַ��Ƿ��ı��ַ���s���ַ���
	return len(t)/len(s) < threshold	# ���û��"from __future__ import division"�����ᱻ�ضϡ�����ضϿ�������'//'������

def chapter1_11():
	''' ������Ⲣû�о�ȷ�㷨����ȫ�������Ե���̽ '''
	print istext('')
	print istext('abcd')
	print istext('aa\0')
	print istext('aa\v\v')

	pass

# ���ƴ�Сд
def chapter1_12():
	print 'aaa'.upper()	# ��Ӧ�Ĳ��Ժ�����isupper()
	print 'AAA'.lower()	# ��Ӧ�Ĳ��Ժ�����islower()
	print 'one tWo thrEe'.capitalize()	# û�ж�Ӧ�Ĳ��Ժ��������Լ򵥵�ʹ�ã�s==s.capitalize()���жϣ��������ڿ��ַ���Ҳ�᷵��True
	print 'one tWo thrEe'.title()	# ��Ӧ�Ĳ��Ժ�����istitle()

	pass

# �������ַ���
import struct
def fields(baseformat, theline, lastfield=False):
	# theline�����ĳ���Ҳ�������base-formatȷ��
	numremain = len(theline) - struct.calcsize(baseformat)
	# �ú��ʵ�s��x�ֶ���ɸ�ʽ��Ȼ��unpack
	format = '%s %d%s' % (baseformat, numremain, lastfield and 's' or 'x')	#  lastfield and 's' or 'x'��Ч���ȼ���C�����е� lastfield ? 's' : 'x'
	return struct.unpack(format, theline)

def split_by(theline, n, lastfield=False):
	# �и�������Ҫ��Ƭ��
	pieces = [theline[k:k+n] for k in xrange(0, len(theline), n)]
	# �����һ��̫�̻�Ҫ������֮
	if not lastfield and len(pieces[-1]) < n:
		pieces.pop()
	return pieces

def split_at(theline, cuts, lastfield=False):
	# �и�������Ҫ��Ƭ��
	pieces = [ theline[i:j] for i, j in zip([0]+cuts, cuts+[None]) ]
	# �����һ��̫�̻�Ҫ������֮
	if not lastfield:
		pieces.pop()
	return pieces

def chapter1_13():
	print 'hello world'[3:8]	# ��Ƭ

	theline = 'abcdefghijklmnopqrstuvwxyz'
	baseformat = '5s 3x 8s 8s'	# �õ�һ��5�ֽڵ��ַ���������3�ֽڣ��õ�����8�ֽ��ַ������Լ����ಿ�֣�
	numremain = len(theline) - struct.calcsize(baseformat)	# theline�����ĳ���Ҳ�������base-formatȷ��
	format = '%s %ds' % (baseformat, numremain)
	l, s1, s2, t = struct.unpack(format, theline)
	print l, s1, s2, t
	l, s1, s2 = struct.unpack(baseformat, theline[:struct.calcsize(baseformat)])	# ���ԡ����ಿ�֡�
	print l, s1, s2

	# ������Ĺ��ܷ�װ��һ������
	l, s1, s2, t = fields(baseformat, theline, True)
	print l, s1, s2, t
	l, s1, s2 = fields(baseformat, theline)
	print l, s1, s2

	# xrange������������ÿ�ε��÷���һ��ֵ����range����list��������ѭ��Ч����xrangeҪ�ߵĶ࣬���Ҳ��ÿ���һ��list�Ŀռ�
	print xrange(0, 10, 5)
	print list(xrange(0, 10, 5))
	print range(0, 10, 5)

	print ['0123456789abc'[k:k+5] for k in xrange(0, 13, 5)]	# ��ƬԽ��Ҳ���ᵼ�³�����󣬵�������̷ǳ�ҵ��

	# ������Ĺ��ܷ�װ��һ������
	print split_by('0123456789abc', 5)

	# zip��������һ��list������ÿ�������(cuts[k], cuts[k+1])���������ԣ����˵�һ������һ�������ֱ���(0, cuts[0])��(cuts[len(cuts)-1], None)
	cuts = [8, 14, 20, 26, 30]
	print [ '000111222333444555666777888999xyz'[i:j] for i, j in zip([0]+cuts, cuts+[None]) ]

	# ������Ĺ��ܷ�װ��һ������
	print split_at('000111222333444555666777888999xyz', cuts)

	pass

# �ı�����ı��ַ���������
def reindent(s, numSpaces):
	leading_space = numSpaces * ' '
	lines = [ leading_space + line.lstrip() for line in s.splitlines() ]
	return '\n'.join(lines)

# more functions about reindent
def addSpaces(s, numAdd):
	white = ' ' * numAdd
	return white + white.join(s.splitlines(True))
def numSpaces(s):
	return [len(line)-len(line.lstrip()) for line in s.splitlines()]
def delSpaces(s, numDel):
	if numDel > min(numSpaces(s)):
		raise ValueError, 'removing more spaces than there are!'
	return '\n'.join([line[numDel:] for line in s.splitlines()])
def unIndentBlock(s):
	return delSpaces(s, min(numSpaces(s)))

def chapter1_14():
	x = '  line one line\n  two and\n  line three'
	print x
	print reindent(x, 4)

	print addSpaces(x,1)
	print numSpaces(x)
	print delSpaces(x, 1)
	print unIndentBlock(x)

	pass

# ��չ��ѹ���Ʊ��
def unexpand(astring, tablen=8):
	import re
	# �зֳɿո�ͷǿո������
	pieces = re.split(r'( +)', astring.expandtabs(tablen))
	# ��¼Ŀǰ�ַ������ܳ���
	lensofar = 0
	for i, piece in enumerate(pieces):
		thislen = len(piece)
		lensofar += thislen
		if piece.isspace():
			# �������ո����иĳ�tabs+spaces
			numblanks = thislen % tablen
			numtabs = (thislen-numblanks)//tablen
			pieces[i] = '\t'*numtabs + ' '*numblanks
	return ''.join(pieces)

def chapter1_15():
	# ���Ʊ���滻Ϊ�ո�
	print len('\tabc'.expandtabs())
	print unexpand('        abc d        e')
	print len('        abc d        e')
	print len(unexpand('        abc d        e'))

	pass

# �滻�ַ����е��Ӵ�
def expand(format, d, marker="'", safe=False):
	if safe:
		def loopup(w): return d.get(w, w.join(marker*2))	# �����ڷ���Ĭ��ֵ
	else:
		def lookup(w): return d[w]	# �������׳��쳣
	parts = format.split(marker)
	parts[1::2] = map(lookup, parts[1::2])	# parts[1::2]���ַ�������������������ǰ���ֻ�޸�list��������
	return ''.join(parts)

def chapter1_16():
	print expand("just 'a' test", {'a': 'one'})
	
	pass

# �滻�ַ����е��ִ�����Python 2.4
import string
def chapter1_17():
	# ���ַ�������ģ�壬���б�ʶ����$���
	new_style = string.Template('this is $thing')
	# ��ģ���substitute��������һ���ֵ����������֮
	print new_style.substitute({'thing':5})
	print new_style.substitute({'thing':'test'})
	# ���⣬Ҳ���Ը�substitute�������ݹؼ��ֲ���
	print new_style.substitute(thing=5)
	print new_style.substitute(thing='test')

	# ʹ������$����$�������ת�⣬������$��ʾ��ӡһ��$
	from_letter = '''Dear $customer,
	i hope you are having a great time.
	if you do not find Room $room to your satisaction,
	let us know. Please accept this $$5 coupon.
			Sincerely,
			$manager
			${name}Inn'''
	letter_template = string.Template(from_letter)
	print letter_template.substitute({'name':'Sleepy', 'customer':'Fred Smith','manager':'Barney Mills', 'room':307,})

	# locals()�������ؽ����ر�������ֵ����ɵ��ֵ�
	msg = string.Template('the square of $number is $square')
	for number in range(10):
		square = number * number
		print msg.substitute(locals())
	# ��һ��������ʹ�ùؼ��ֶ����ֵ�
	msg = string.Template('the square of $number is $square')
	for i in range(10):
		print msg.substitute(number=i, square=i*i)
	# ��������ͬʱ�����ֵ�͹ؼ��ֲ���
	msg = string.Template('the square of $number is $square')
	for number in range(10):
		print msg.substitute(locals(), square=number*number)
	# Ϊ�˷�ֹ�ֵ����Ŀ��ؼ��ֲ�����ʽ���ݵ�ֵ������ͻ���ؼ��ֲ�������
	msg = string.Template('an $adj $msg')
	adj = 'interesting'
	print msg.substitute(locals(), msg='message')


	pass

# һ����ɶ���滻
import re
def multiple_replace(text, adict):
	rx = re.compile('|'.join(map(re.escape, adict)))	# map������dict����ʱ��ֻ����dict��key��������value
	def one_xlat(match):
		return adict[match.group(0)]
	return rx.sub(one_xlat, text)	# sub�ĵ�һ�������������ַ�����Ҳ�����Ǻ���

def make_xlat(*args, **kwds):
	''' ���Զ���ı�ʹ��ͳһ������ʱ��ʹ�û��ڱհ��ķ�ʽֻ����һ��׼���������������Ч�� '''
	adict = dict(*args, **kwds)	# ��*��**ʹ�ò�����������ʾԭ�����ݣ����벻��*��**������ȫ��ͬ���Ƚϸ��ӣ���׸����
	rx = re.compile('|'.join(map(re.escape, adict)))
	def one_xlat(match):
		return adict[match.group(0)]
	def xlat(text):
		return rx.sub(one_xlat, text)
	return xlat
class make_xlat_class:
	''' ��������ʽ�����޸�ʱ�����ǿ������������������������Ĵ��븴��
	    ��Ȼ�������Ӽ򵥿��٣�����������ô������������� '''
	def __init__(self, *args, **kwds):
		self.adict = dict(*args, **kwds)
		self.rx = self.make_rx()
	def make_rx(self):
		return re.compile('|'.join(map(re.escape, self.adict)))
	def one_xlat(self, match):
		return self.adict[match.group(0)]
	def __call__(self, text):
		return self.rx.sub(self.one_xlat, text)
class make_xlat_by_whole_words(make_xlat_class):
	def make_rx(self):
		return re.compile(r'\b%s\b' % r'\b|\b'.join(map(re.escape, self.adict)))
def chapter1_18():
	text = 'Larry Wall is the creator of Perl'
	adict = {
			'Larry Wall' : 'Guido van Rossum',
			'creator' : 'Benevolent Dictator for Life',
			'Perl' : 'Python'
			}

	print multiple_replace(text, adict)
	translate = make_xlat(adict)
	print translate(text)

	translate = make_xlat_class(adict)
	print translate(text)
	translate = make_xlat_by_whole_words(adict)
	print translate(text)

	pass

# ����ַ����н������
import itertools	# itertools�ĸ�Ч����Ҫ�Ը�ģ���������ѧϰ
def anyTrue(predicate, sequence):	# itertools.imap������һ�ֿ��ٷ���Ľ���취
	return True in itertools.imap(predicate, sequence)
def endsWith(s, *endings):
	return anyTrue(s.endswith, endings)
def chapter1_19():
	print 'hello world'.endswith('ld')	# ����һ����ֱ�ӣ�������صķ���
	print endsWith('hello world', 'ld')

	pass

# ʹ��Unicode��������ʻ��ı�
def chapter1_20():
	german_ae = unicode('\xc3\xa4', 'utf8')
	print german_ae

	# ����������ͨstr�ַ�����������unicode�ַ���
	s = 'this is a ' + german_ae
	s2 = 'easy!'
	para = '. '.join([s, s2])
	print para

	pass

#	bytestring = '\xc3\xa4'	# ���Ǹ���ASCII�ַ��������ֲ����������׳��쳣
#	german_ae += bytestring

# ��Unicode����ͨ�ַ���֮��ת��
def chapter1_21():
	unicodestring = u'Hello World'
	# ��Unidoceת��Ϊ��ͨ�ַ���: "encode"
	utf8string = unicodestring.encode('utf-8')
	asciistring = unicodestring.encode('ascii')
	isostring = unicodestring.encode('ISO-8859-1')
	utf16string = unicodestring.encode('utf-16')
	# ����ͨ�ַ���ת��Ϊunicode: "decode"
	plainstring1 = unicode(utf8string, 'utf-8')
	plainstring2 = unicode(asciistring, 'ascii')
	plainstring3 = unicode(isostring, 'ISO-8859-1')
	plainstring4 = unicode(utf16string, 'utf-16')
	assert plainstring1 == plainstring2 == plainstring3 == plainstring4

	pass

# �ڱ�׼����д�ӡUnicode�ַ�
import codecs, sys
def chapter1_22():
	# ��sys.stdout����ת������װ����
	old = sys.stdout
	sys.stdout = codecs.lookup('iso8859-1')[-1](sys.stdout)
	sys.stdout = old

	# ���һ��unicode�ַ���
	# ����׳��쳣������Pythonû���Զ�ʶ�����ȷ�ı��룩������Ҫʹ������������stdout���а�װ
	char = u'\N{LATIN SMALL LETTER A WITH DIAERESIS}'
	print char

	pass

# ��Unicode���ݱ��벢����XML��HTML
def encode_for_xml(unicode_data, encoding = 'ascii'):
	''' python�ṩ��һ�ֱ���������ߣ�����xmlcharrefreplace��
	���Ὣ���в�������ѡ������ַ���XML�������ַ����������� '''
	return unicode_data.encode(encoding, 'xmlcharrefreplace')

import codecs
from htmlentitydefs import codepoint2name
def html_replace(exc):
	''' ע��һ���Զ���ı���������������ڴ���HTML��� '''
	if isinstance(exc, (UnicodeEncodeError, UnicodeTranslateError)):
		s = [u'&%s;' % codepoint2name[ord(c)]
				for c in exc.object[exc.start:exc.end]]
		return ''.join(s), exc.end
	else:
		raise TypeError("can't handle %s" % exc.__name__)

def encode_for_html(unicode_data, encoding = 'ascii'):
	return unicode_data.encode(encoding, 'html_replace')
		
def chapter1_23():
	data = u'''\
<html>
	<head>
		<title>Encoding Test</title>
	</head>
	<body>
		<p>accented characters:
		<ul>
			<li>\xe0 (a + grave)
			<li>\xe7 (c + cedilla)
			<li>\xe9 (e + acute)
		</ul> 
		<p>symbols:
		<ul>
			<li>\xa3 (British pound)
			<li>\u20ac (Euro)
			<li>\u221e (infinity)
		</ul>
	</body>
</html>''' 
	print encode_for_xml(data)
	codecs.register_error('html_replace', html_replace)
	print encode_for_html(data)

	pass

# ��ĳЩ�ַ�����Сд������
class iStr(str):
	'''
	��Сд�����е��ַ�����
	��Ϊ��ʽ������str��ֻ�����еıȽϺͲ�ѯ
	���Ǵ�Сд�����е�
	'''
	def __init__(self, *args):
		self._lowered = str.lower(self)
	def __repr__(self):
		return '%s(%s)' % (type(self).__name__, str.__repr__(self))
	def __hash__(self):
		return hash(self._lowered)
	def lower(self):
		return self._lowered

def _make_case_insensitive(name):
	''' ��str�ķ�����װ��iStr�ķ�������Сд������ '''
	str_meth = getattr(str, name)
	def x(self, other, *args):
		'''
		�ȳ��Խ�otherСд����ͨ����Ӧ����һ���ַ�����
		������Ҫ����׼��Ӧ����������г��ֵĴ���
		��Ϊ�ַ����ǿ��Ժͷ��ַ�����ȷ�Ƚϵ�
		'''
		try : other = other.lower()
		except (TypeError, AttributeError, ValueError):pass
		return str_meth(self._lowered, other, *args)
	# ��python 2.4������һ����䣺x.func_name = name
	setattr(iStr, name, x)

def _make_return_iStr(name):
	''' �����еķ����ַ�����iStr������װ
	ʹ�����еķ��ؽ������iStr���ͣ�������Ĭ�ϵ�str����'''
	str_meth = getattr(str, name)
	def x(*args):
		return iStr(str_meth(*args))
	setattr(iStr, name, x)

def chapter1_24():
	global _make_case_insensitive	# ������global��delʱ������
	for name in 'eq lt le gt gt ne contains'.split():
		_make_case_insensitive('__%s__' % name)
	for name in 'count endswith find index rfind rindex startswith'.split():
		_make_case_insensitive(name)
	# ע�⣬���ǲ����޸�replace��split��strip�ȷ���
	# ��Ȼ���������Ҫ��Ҳ���Զ����ǽ����޸�
	del _make_case_insensitive	# ɾ�������������Ѿ�������Ҫ��

	s1 = 'hello'
	s2 = 'HELLO'
	print s1 == s2

	s1 = iStr('hello')
	s2 = iStr('HELLO')
	print s1 == s2

	print type(s1.strip())
	for name in 'center ljust rjust strip lstrip rstrip'.split():
		_make_return_iStr(name)
	print type(s2.strip())

	# ����P51ҳ������һ������iStrʵ�ִ�Сд�޹ص�iList

	pass

# ��HTML�ĵ�ת��Ϊ�ı���ʾ��UNIX�ն���
import sys, os, htmllib, formatter
# ʹ��UNIX��tput����ô��塢�»��ߺ������ת������
set_bold = os.popen('tput bold').read()
set_underline = os.popen('tput smul').read()
perform_reset = os.popen('tput sgr0').read()
class TtyFormatter(formatter.AbstractFormatter):
	''' һ�����������б��״̬�ĸ�ʽ������
	�������Ӧ���ն˿������� '''
	def __init__(self, writer):
		# ���ȣ�������һ������ʼ������
		formatter.AbstractFormatter.__init__(self, writer)
		# һ��ʼ��û�д���Ҳû��б��״̬��δ�����κ���Ϣ
		self.fontState = False, False
		self.fontStack = []
	def push_font(self, font):
		# fontԪ����4� ����ֻ��������б���״̬�йص�������־
		size, is_italic, is_bold, is_tt = font
		self.fontStack.append((is_italic, is_bold))
		self._updateFontState()
	def pop_font(self, *args):
		# �ص�ǰһ��font״̬
		try:
			self.fontStack.pop()
		except IndexError:
			pass
		self._updateFontState
	def updateFontState(self):
		# �����ȷ���ն˿������У���������/��б��(==underline)
		# ��״̬�ոձ��ı�Ļ�
		try:
			newState = self.fontStack[-1]
		except IndexError:
			newState = False, False
		if self.fontState != newState:
			# ��ص�״̬�ı䣺�����ն�
			print perform_reset,
			# �����Ҫ�Ļ��������»�����/�����״̬
			if newState[0]:
				print set_underline,
			if newState[1]:
				print set_bold,
			# ��ס��ǰ������״̬
			self.fontState = newState
def chapter1_25():
	# ����д�롢��ʽ�����������󣬸�����Ҫ��������������
	myWriter = formatter.DumbWriter()
	if sys.stdout.isatty():
		myFormatter = TtyFormatter(myWriter)
	else:
		myFormatter = formatter.AbstractFormatter(myWriter)
	myParser = htmllib.HTMLParser(myFormatter)
	# ����׼������ն˲����ṩ��������
	myParser.feed(sys.stdin.read())
	myParser.close()

	pass

def main():
#	chapter1_1()
#	chapter1_2()
#	chapter1_3()
#	chapter1_4()
#	chapter1_5()
#	chapter1_6()
#	chapter1_7()
#	chapter1_8()
#	chapter1_9()
#	chapter1_10()
#	chapter1_11()
#	chapter1_12()
#	chapter1_13()
#	chapter1_14()
#	chapter1_15()
#	chapter1_16()
#	chapter1_17()
#	chapter1_18()
#	chapter1_19()
#	chapter1_20()
#	chapter1_21()
#	chapter1_22()
#	chapter1_23()
#	chapter1_24()
	chapter1_25()	# ���ʵ��û����

	pass

if __name__ == '__main__':
	main()
