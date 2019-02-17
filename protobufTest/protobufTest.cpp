#include "protobufTest.h"
#include "test.pb.h"
#include <iostream>
#include "glog/logging.h"

protobufTest::protobufTest(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	test();
	testPOD();
}

void protobufTest::test()
{
	using namespace std;
	addressbook::AddressBook person;
	addressbook::Person *pi = person.add_person_info();

	pi->set_name("aut");
	pi->set_id(1219);
	LOG(INFO) << "before clear(),id= " << pi->id() << std::endl;
	pi->clear_id();
	LOG(INFO) << "after clear(),id= " << pi->id() << std::endl;
	pi->set_id(1087);
	if (!pi->has_email())
		pi->set_email("zhao@136.com");

	addressbook::Person::PhoneNumber *pn = pi->add_phone();
	pn->set_number("021-1234");
	pn = pi->add_phone();
	pn->set_number("1381234567");
	pn->set_type(addressbook::Person_PhonType_MOBILE);

	uint32_t size = person.ByteSize();
	unsigned char byteArray[100000] = { 0 };
	person.SerializeToArray(byteArray, size);

	addressbook::AddressBook help_person;
	help_person.ParseFromArray(byteArray, size);
	print(help_person);	

	typedef addressbook::AddressBook T;

	std::string type_name = T::descriptor()->full_name();
	LOG(INFO) << type_name << endl;

	//1.根据类型全名找Descriptor
	const google::protobuf::Descriptor* descriptor = google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);
	assert(descriptor == T::descriptor());
	LOG(INFO) << "FindMessageTypeByName() = " << descriptor << endl;
	LOG(INFO) << "T::descriptor()         = " << T::descriptor() << endl;
	LOG(INFO) << endl;

	//2.根据Descriptor找原型
	const google::protobuf::Message* prototype = google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
	assert(prototype == &T::default_instance());
	LOG(INFO) << "GetPrototype()        = " << prototype << endl;
	LOG(INFO) << "T::default_instance() = " << &T::default_instance() << endl;
	LOG(INFO) << endl;

	//3.根据原型创建所需类型的对象,其实只需知道具体类型的字符串即可,不用转换为具体的类型
	T* new_obj = dynamic_cast<T*>(prototype->New());
	assert(new_obj != NULL);
	assert(new_obj != prototype);
	assert(typeid(*new_obj) == typeid(T::default_instance()));
	LOG(INFO) << "prototype->New() = " << new_obj << endl;
	LOG(INFO) << endl;

	new_obj->ParseFromArray(byteArray,size);//
	print(*new_obj);

	google::protobuf::Message* pMsg = prototype->New();
	LOG(INFO) << "pMsg"<<pMsg->GetDescriptor()->full_name()<<endl;
	pMsg->ParseFromArray(byteArray, size);
	print(*static_cast<addressbook::AddressBook*>(pMsg));
	delete new_obj;
}

void protobufTest::testPOD()
{
	LOG(INFO) << "Trival : " << std::is_trivial<Trival>() <<std::is_pod<Trival>()<< std::endl;
}

void protobufTest::print(const addressbook::AddressBook &info)
{
	uint32_t personNum = info.person_info_size();
	addressbook::Person help_pi = info.person_info(0);

	LOG(INFO) << "*****************************" << std::endl;
	LOG(INFO) << "id:    " << help_pi.id() << std::endl;
	LOG(INFO) << "name:  " << help_pi.name() << std::endl;
	LOG(INFO) << "email: " << help_pi.email() << std::endl;

	for (int i = 0; i < help_pi.phone_size(); ++i)
	{
		auto help_pn = help_pi.mutable_phone(i);
		LOG(INFO) << "phone_type: " << help_pn->type() << std::endl;
		LOG(INFO) << "phone_number: " << help_pn->number() << std::endl;
	}
	LOG(INFO) << "*****************************" << std::endl;
}

